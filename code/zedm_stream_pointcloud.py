import argparse
from math import ceil, pi
from tabnanny import verbose
import pyzed.sl as sl
from signal import signal, SIGINT
import sys
import segmentation as seg
import cv2
import PIL
import numpy as np
import pickle
import time
import matlab.engine


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


def GenerateFrameZed(zed):
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


def draw_top_down(a, *, pic = None, color = (0, 200, 0)):
    if pic is None:
        pic = np.full((img_dims[1], img_dims[0], 3), (255, 255, 255), np.uint8)
    drivable = scale_xy_to_img(a)
    for x, y in drivable:
        pic[y, x] = color
    return pic

def replace_pixels(a, find, replace):
    a[(a == find).all(axis=-1)] = replace

# Note: the Stereolabs API zed.find_floor_plane can sometimes cause a segmentation fault!
# Test on indoor.svo towards the end of the hallway
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
    point_cloud = sl.Mat()
    status = zed.retrieve_measure(point_cloud, sl.MEASURE.XYZRGBA)
    if status != sl.ERROR_CODE.SUCCESS:
        print("Could not retrieve point cloud")
        return None
    point_cloud = point_cloud.get_data().reshape(-1, 4)[:, (0, 2)]
    fil = out.flatten() != 0
    # We want to filter out non-seg pixels from the point cloud,
    # so we're left with (x, z) coordinates that are drivable.
    return draw_top_down(remove_sub_nans(point_cloud[fil]))


# POINT CLOUD PROCESSING
floor_height_error = 15.0  # +- mm
# there is a negative gradient due to tilt on the sensor mount
# z is negative in front of us
# This is usually characterised as 0.145
floor_gradient = 0.145
gradient_error = 0.00
upper_floor_gradient = floor_gradient - gradient_error
lower_floor_gradient = floor_gradient + gradient_error
min_obstacle_height = 400.0 # mm
max_obstacle_height = 410.0 # mm

def find_floor(zed):
    pcloud = sl.Mat()
    status = zed.retrieve_measure(pcloud, sl.MEASURE.XYZRGBA)
    if status != sl.ERROR_CODE.SUCCESS:
        print("Could not retrieve point cloud")
        return None
    pcloud = remove_sub_nans(pcloud.get_data().reshape(-1, 4))  # remove nans from the point cloud
    y = pcloud[:,1] - pcloud[:,2] * floor_gradient + floor_height_prior
    #pcloud = pcloud[:, (0, 2)]
    #levels = pcloud[:,1] * floor_gradient - floor_height_prior
    upper_bound = -pcloud[:,2] * gradient_error + floor_height_error
    lower_bound = pcloud[:,2] * gradient_error - floor_height_error
    pic = draw_top_down(pcloud[np.logical_and(y < upper_bound, y > lower_bound)])
    # Lets try coloring in obstacles too
    obstacle_criteria = np.logical_and(y > min_obstacle_height, y < max_obstacle_height)
    pic = draw_top_down(pcloud[obstacle_criteria], pic=pic, color=(0, 0, 200))
    return pic


# FIRST CONTROL ALGORITHM - MATLAB INTERFACE
def control_avoid_walls(eng, map):
    pose = matlab.double([5, 0, pi / 2])
    # 3rd channel red (200) pixels are walls, white (255) if clear
    # convert to true if obstacle, false if not
    v = (map[:,:,2] == 200).tolist()
    mapmat = matlab.logical(v)
    steerDir, vfh, scan, binmap, vfhfig, otherfig = eng.vfhControllerCoder(pose, 0.0, mapmat, 1000.0 / scale, nargout=6)
    return eng.getframe(vfhfig, nargout=1), eng.getframe(otherfig, nargout=1)


def main():
    # Initialization
    p = seg.VideoProperties(30, 1920, 1080)
    generate_frame = GenerateFrameZed(cleanup.zed)
    cleanup.push_frame = seg.PushFrame((p, "capture.mp4"), "camera", cv2.WINDOW_FULLSCREEN)
    push_frame_floor_plane = seg.PushFrame((seg.VideoProperties(fps, img_dims[0], img_dims[1]), "floor_plane.mp4"), "floor_plane")
    push_frame_segmentation = seg.PushFrame((seg.VideoProperties(fps, img_dims[0], img_dims[1]), "segmentation.mp4"), "segmentation")
    cleanup.push_frame_floor_cloud = seg.PushFrame((seg.VideoProperties(fps, img_dims[0], img_dims[1]), "pcloud.mp4"), "floor_cloud")
    model, draw_frame = seg.HybridnetLoader(p)#, "../models/hybridnet_epoch_1.pth")
    #kernel_sz = max(2, round(1 / scale * 100))
    #print(f"Kernel size: {kernel_sz}")
    kernel = np.ones((10, 10), np.uint8)

    skip_frames = 30 // fps
    for i, image in enumerate(generate_frame()):
        image_rgb = np.delete(image, 3, 2)
        if skip_frames != 0 and i % skip_frames != 0:
            #push_frame_segmentation(floor_seg)
            cleanup.push_frame_floor_cloud(floor_cloud)
            cleanup.push_frame(image_rgb)
            continue
        start_time = time.time()
        # CAMERA LEFT VIEW
        if cv2.waitKey(1) == ord('q'):
            break


        # FLOOR PLANE
        # print("Floor plane")
        #floor_plane = detect_floor_plane(cleanup.zed)
        #if floor_plane is not None:
        #    push_frame_floor_plane(floor_plane)

        # SEGMENTATION
        # print("Floor seg")
        #image_rgb = np.delete(image, 3, 2)
        #out = model(image_rgb)
        #image_rgb = draw_frame(image_rgb, out)
        #floor_seg = project_segmentation(cleanup.zed, out)
        #if floor_seg is not None:
            #floor_seg = cv2.erode(floor_seg, kernel)
        #    push_frame_segmentation(floor_seg)

        # FLOOR POINT CLOUD PROCESSING
        # print("Floor cloud")
        floor_cloud = find_floor(cleanup.zed)
        if floor_cloud is not None:
            floor_cloud = cv2.erode(floor_cloud, kernel)
            replace_pixels(floor_cloud, (0, 0, 0), (0, 0, 200))
            cleanup.push_frame_floor_cloud(floor_cloud)

        ret = control_avoid_walls(cleanup.eng, floor_cloud)
        cleanup.vfh_frame.append(ret[0])
        cleanup.control_frame.append(ret[1])

        cleanup.push_frame(image_rgb)
        elapsed_time = time.time() - start_time
        print(f"Frame count: {i}, FPS: {1 / elapsed_time}", end="\r")
    # Cleanup
    #push_frame(None)
    #push_frame_floor_plane(None)
    push_frame_segmentation(None)
    #push_frame_floor_cloud(None)
    push_frame_floor_plane(None)

class Cleanup:
    def __init__(self):
        signal(SIGINT, self.syshandler)
        self.zed = sl.Camera()
        self.eng = matlab.engine.start_matlab(option="-sd ./matlab")
        self.push_frame = None
        self.push_frame_floor_cloud = None
        self.vfh_frame = []
        self.control_frame = []

    def syshandler(self, signal_recieved, frame):
        self.handler()

    def handler(self):
        self.push_frame(None)
        self.push_frame_floor_cloud(None)
        self.zed.close()
        #self.eng.workspace['control_frame'] = self.control_frame
        #self.eng.workspace['vfh_frame'] = self.vfh_frame
        #self.eng.save('frames.mat', 'control_frame', 'vfh_frame', nargout=0)
        self.eng.videoWriterHelper('vfh_frame.mp4', self.vfh_frame, matlab.double(fps), nargout=0)
        self.eng.videoWriterHelper('control_frame.mp4', self.control_frame, matlab.double(fps), nargout=0)
        sys.exit(0)


if __name__ == "__main__":
    fps = 5
    cleanup = Cleanup()
    main()
    cleanup.handler()
