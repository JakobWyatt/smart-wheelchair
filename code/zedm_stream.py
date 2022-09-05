import argparse
from math import ceil
import pyzed.sl as sl
from signal import signal, SIGINT
import sys
import segmentation as seg
import cv2
import PIL
import numpy as np
import pickle

zed = sl.Camera()


def handler(signal_received, frame):
    zed.close()
    sys.exit(0)


signal(SIGINT, handler)


## NOTE: Attempting to print large arrays on windows will lead to a crash.

def StreamInitParams(params):
    parser = argparse.ArgumentParser()
    parser.add_argument('--source', type=str, help='svo path')
    args = parser.parse_args()
    if args.source is None:
        return params
    params.set_from_svo_file(args.source)
    params.svo_real_time_mode = True
    return params


def GenerateFrameZed():
    # Set up parameters
    init_params = sl.InitParameters()
    init_params.camera_resolution = sl.RESOLUTION.HD1080
    init_params = StreamInitParams(init_params)
    init_params.depth_mode = sl.DEPTH_MODE.ULTRA
    init_params.coordinate_units = sl.UNIT.MILLIMETER
    init_params.coordinate_system = sl.COORDINATE_SYSTEM.RIGHT_HANDED_Y_UP

    runtime_params = sl.RuntimeParameters()

    # Initialize camera
    status = zed.open(init_params)
    if status != sl.ERROR_CODE.SUCCESS:
        print(repr(status))
        exit(1)

    zed_serial = zed.get_camera_information().serial_number
    print("ZED serial number: {0}".format(zed_serial))

    image = sl.Mat()

    def generate_frame():
        while True:
            status = zed.grab(runtime_params)
            if status == sl.ERROR_CODE.SUCCESS:
                zed.retrieve_image(image)
                yield image.get_data()
            elif status == sl.ERROR_CODE.END_OF_SVOFILE_REACHED:
                return
            else:
                print("Frame")
                print(repr(status))
                print("Failed")

    return generate_frame


############## DIFFERENT PROCESSING METHODS ATTEMPTED #################

# FLOOR PLANE DETECTION
scale = 25  # mm/pix
physical_dims = (10000, 15000)  # 10m x (Centered), 15m z (-ve)
img_dims = (int(physical_dims[0] / scale), int(physical_dims[1] / scale))
floor_height_prior = 740.0  # mm


def scale_xy_to_img(p):
    x = np.clip(p[:, 0] / scale + img_dims[0] / 2, 1, img_dims[0] - 1)
    y = np.clip(p[:, 1] / scale + img_dims[1], 1, img_dims[1] - 1)
    return np.column_stack((x, y)).astype(np.int32)


def remove_sub_nans(a):
    return a[~np.isnan(a).any(1)]


def draw_top_down(a, pic):
    #pic = np.zeros((*img_dims, 3),
    drivable = scale_xy_to_img(a).tolist()
    for x, y in drivable:
        pic.putpixel((x, y), (0, 200, 0))

# Note: the Stereolabs API zed.find_floor_plane can sometimes cause a segmentation fault!
# No way to catch this :(
def detect_floor_plane(zed):
    plane = sl.Plane()
    reset_tracking_floor_frame = sl.Transform()
    status = zed.find_floor_plane(plane, reset_tracking_floor_frame, floor_height_prior)
    if status != sl.ERROR_CODE.SUCCESS:
        print("No floor plane detected")
        return None
    birds_eye = PIL.Image.new('RGB', img_dims, color='white')
    draw = PIL.ImageDraw.Draw(birds_eye)
    p = plane.get_bounds()
    p = p[p[:, 2] < 0]  # Clean the image by not placing polygons behind us.
    polygon = scale_xy_to_img(remove_sub_nans(p)).flatten().tolist()
    if len(polygon) < 3:
        print("Invalid floor plane detected")
        return None
    draw.polygon(polygon, fill=(0, 200, 0), width=10)
    return np.array(birds_eye, dtype=np.uint8)


# SEGMENTATION
def project_segmentation(zed, out):
    birds_eye = PIL.Image.new('RGB', img_dims, color='white')
    point_cloud = sl.Mat()
    status = zed.retrieve_measure(point_cloud, sl.MEASURE.XYZRGBA)
    if status != sl.ERROR_CODE.SUCCESS:
        print("Could not retrieve point cloud")
        return None
    point_cloud = point_cloud.get_data().reshape(-1, 4)[:, (0, 2)]
    fil = out.flatten() != 0
    # We want to filter out non-seg pixels from the point cloud,
    # so we're left with (x, z) coordinates that are drivable.
    draw_top_down(remove_sub_nans(point_cloud[fil]), birds_eye)
    return np.array(birds_eye, dtype=np.uint8)


# POINT CLOUD PROCESSING
floor_height_error = 150.0  # +- mm
# there is a negative gradient due to tilt on the sensor mount
# z is negative in front of us
# This is usually characterised as 0.145
upper_floor_gradient = 0.2


def find_floor(zed):
    birds_eye = PIL.Image.new('RGB', img_dims, color='white')
    pcloud = sl.Mat()
    status = zed.retrieve_measure(pcloud, sl.MEASURE.XYZRGBA)
    if status != sl.ERROR_CODE.SUCCESS:
        print("Could not retrieve point cloud")
        return None
    pcloud = remove_sub_nans(pcloud.get_data().reshape(-1, 4))  # remove nans from the point cloud
    y = pcloud[:, 1]
    pcloud = pcloud[:, (0, 2)]
    upper_bound = pcloud[:, 1] * upper_floor_gradient - floor_height_prior + floor_height_error
    draw_top_down(pcloud[y < upper_bound], birds_eye)
    return np.array(birds_eye, dtype=np.uint8)


def main():
    # Initialization
    generate_frame = GenerateFrameZed()
    push_frame = seg.PushFrame(None, "camera", cv2.WINDOW_FULLSCREEN)
    #push_frame_floor_plane = seg.PushFrame(None, "floor_plane")
    push_frame_segmentation = seg.PushFrame(None, "segmentation")
    push_frame_floor_cloud = seg.PushFrame(None, "floor_cloud")
    p = seg.VideoProperties(30, 1920, 1080)
    model, draw_frame = seg.HybridnetLoader(p)  # , "../models/hybridnet_epoch_1.pth")
    #kernel_sz = max(2, round(1 / scale * 100))
    #print(f"Kernel size: {kernel_sz}")
    kernel = np.ones((10, 10), np.uint8)

    for i, image in enumerate(generate_frame()):
        # CAMERA LEFT VIEW
        if cv2.waitKey(1) == ord('q'):
            break
        print("Frame count: " + str(i), end="\r")


        # FLOOR PLANE
        # print("Floor plane")
        #floor_plane = detect_floor_plane(zed)
        #if floor_plane is not None:
        #    push_frame_floor_plane(floor_plane)

        # SEGMENTATION
        # print("Floor seg")
        image_rgb = np.delete(image, 3, 2)
        out = model(image_rgb)
        image = draw_frame(image_rgb, out)
        floor_seg = project_segmentation(zed, out)
        if floor_seg is not None:
            floor_seg = cv2.erode(floor_seg, kernel)
            push_frame_segmentation(floor_seg)

        # FLOOR POINT CLOUD PROCESSING
        # print("Floor cloud")
        floor_cloud = find_floor(zed)
        if floor_cloud is not None:
            floor_cloud = cv2.erode(floor_cloud, kernel)
            push_frame_floor_cloud(floor_cloud)

        push_frame(image)
    # Cleanup
    push_frame(None)
    #push_frame_floor_plane(None)
    push_frame_segmentation(None)
    push_frame_floor_cloud(None)


if __name__ == "__main__":
    main()
