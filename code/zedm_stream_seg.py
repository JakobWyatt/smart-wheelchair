import argparse
from math import ceil, pi
import pyzed.sl as sl
from signal import signal, SIGINT
import sys
import segmentation as seg
import cv2
import PIL
import numpy as np
import time


## NOTE: Attempting to print large arrays on windows will lead to a crash.

def StreamInitParams(params):
    parser = argparse.ArgumentParser()
    parser.add_argument('--source', type=str, help='svo path')
    args = parser.parse_args()
    if args.source is None:
        return params
    params.set_from_svo_file(args.source)
    params.svo_real_time_mode = False
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

def main():
    # Initialization
    p = seg.VideoProperties(30, 1920, 1080)
    generate_frame = GenerateFrameZed(cleanup.zed)
    cleanup.push_frame = seg.PushFrame((p, "capture.mp4"), "camera", cv2.WINDOW_FULLSCREEN)
    cleanup.push_frame_segmentation = seg.PushFrame((seg.VideoProperties(fps, img_dims[0], img_dims[1]), "segmentation.mp4"), "segmentation")
    model, draw_frame = seg.HybridnetLoader(p)
    #kernel_sz = max(2, round(1 / scale * 100))
    #print(f"Kernel size: {kernel_sz}")
    kernel = np.ones((10, 10), np.uint8)

    skip_frames = 30 // fps
    for i, image in enumerate(generate_frame()):
        image_rgb = np.delete(image, 3, 2)
        if skip_frames != 0 and i % skip_frames != 0:
            cleanup.push_frame(image_seg)
            continue
        start_time = time.time()
        # CAMERA LEFT VIEW
        if cv2.waitKey(1) == ord('q'):
            break

        # SEGMENTATION
        # print("Floor seg")
        #image_rgb = np.delete(image, 3, 2)
        out = model(image_rgb)
        image_seg = draw_frame(image_rgb, out)
        floor_seg = project_segmentation(cleanup.zed, out)
        if floor_seg is not None:
            floor_seg = cv2.erode(floor_seg, kernel)
            cleanup.push_frame_segmentation(floor_seg)

        cleanup.push_frame(image_seg)
        elapsed_time = time.time() - start_time
        print(f"Frame count: {i}, FPS: {1 / elapsed_time}", end="\r")

class Cleanup:
    def __init__(self):
        signal(SIGINT, self.syshandler)
        self.zed = sl.Camera()
        self.push_frame = None
        self.push_frame_segmentation = None
        self.vfh_frame = []
        self.control_frame = []

    def syshandler(self, signal_recieved, frame):
        self.handler()

    def handler(self):
        self.push_frame(None)
        self.push_frame_segmentation(None)
        self.zed.close()
        sys.exit(0)


if __name__ == "__main__":
    fps = 5
    cleanup = Cleanup()
    main()
    cleanup.handler()
