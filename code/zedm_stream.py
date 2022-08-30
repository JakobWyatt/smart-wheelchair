import argparse
import pyzed.sl as sl
from signal import signal, SIGINT
import sys
import segmentation as seg
import cv2
import PIL
import numpy as np

zed = sl.Camera()

def handler(signal_received, frame):
    zed.close()
    sys.exit(0)

signal(SIGINT, handler)

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
                print(repr(status))
    return generate_frame

############## DIFFERENT PROCESSING METHODS ATTEMPTED #################

# FLOOR PLANE DETECTION
scale = 10 # pix/mm
dims = (1000, 1500) # 10m x (Centered), 15m z (-ve)

def scale_xy_to_img(p):
        x = np.clip(p[:,0] / scale + dims[0] / 2, 1, dims[0] - 1)
        y = np.clip(p[:,1] / scale + dims[1], 1, dims[1] - 1)
        return np.column_stack((x, y)).astype(np.int32)

def detect_floor_plane(zed):
    plane = sl.Plane()
    reset_tracking_floor_frame = sl.Transform()
    floor_height_prior = 740 #mm
    status = zed.find_floor_plane(plane, reset_tracking_floor_frame, floor_height_prior)
    if status == sl.ERROR_CODE.SUCCESS:
        # init image, birds eye view
        birds_eye = PIL.Image.new('RGB', dims, color='white')
        draw = PIL.ImageDraw.Draw(birds_eye)
        p = plane.get_bounds()
        p = p[p[:,2] < 0] # reshape and filter
        draw.polygon(scale_xy_to_img(p).flatten().tolist(), outline=255, width=10)
        return np.array(birds_eye, dtype=np.uint8)
    else:
        print(repr(status))
        return None


# SEGMENTATION
def project_segmentation(zed, out):
    birds_eye = PIL.Image.new('RGB', dims, color='white')
    point_cloud = sl.Mat()
    zed.retrieve_measure(point_cloud, sl.MEASURE.XYZRGBA)
    point_cloud = point_cloud.get_data().reshape(-1, 4)[:,(0,2)]
    fil = out.flatten() != 0
    # We want to filter out non-seg pixels from the point cloud,
    # so we're left with (x, z) coordinates that are drivable.
    drivable = scale_xy_to_img(point_cloud[fil]).tolist()
    for x, y in drivable:
        try:
            birds_eye.putpixel((x, y), 255)
        except Exception:
            # Some weird integer overflow going on, should fix before I submit my thesis
            pass
    return np.array(birds_eye, dtype=np.uint8)


def main():
    # Initialization
    generate_frame = GenerateFrameZed()
    push_frame = seg.PushFrame()
    push_frame_birdseye = seg.PushFrame(None, "birdseye")
    push_frame_birdseyep = seg.PushFrame(None, "birdseyep")
    p = seg.VideoProperties(30, 1920, 1080)
    model, draw_frame = seg.HybridnetLoader(p)#, "../models/hybridnet_epoch_1.pth")

    for i, image in enumerate(generate_frame()):
        # CAMERA LEFT VIEW
        if cv2.waitKey(1) == ord('q'):
            break
        print("Frame count: " + str(i), end="\r")

        # FLOOR PLANE
        floor_plane = detect_floor_plane(zed)
        if floor_plane is not None:
            push_frame_birdseye(floor_plane)

        # SEGMENTATION
        image_rgb = np.delete(image, 3, 2)
        out = model(image_rgb)
        image = draw_frame(image_rgb, out)
        floor_seg = project_segmentation(zed, out)
        push_frame_birdseyep(floor_seg)

        push_frame(image)
    # Cleanup
    push_frame(None)
    push_frame_birdseye(None)
    push_frame_birdseyep(None)


if __name__ == "__main__":
    main()
