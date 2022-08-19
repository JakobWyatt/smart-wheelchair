import argparse
import pyzed.sl as sl
from signal import signal, SIGINT
import sys
import segmentation as seg
import cv2

zed = sl.Camera()

def handler(signal_received, frame):
    zed.close()
    sys.exit(0)

signal(SIGINT, handler)

def GenerateFrameZed(source: str):
    # Set up parameters
    init_params = sl.InitParameters()
    runtime_params = sl.RuntimeParameters()
    # DEPTH_MODE.NEURAL is best
    # use DEPTH_MODE.PERFORMANCE for now
    if source is not None:
        init_params.set_from_svo_file(source)
        init_params.svo_real_time_mode = False
        init_params.depth_mode = sl.DEPTH_MODE.PERFORMANCE
    else:
        init_params.camera_resolution = sl.RESOLUTION.HD1080
        init_params.depth_mode = sl.DEPTH_MODE.PERFORMANCE

    # Initialize camera
    status = zed.open(init_params)
    if status != sl.ERROR_CODE.SUCCESS:
        print(repr(status))
        exit(1)

    if source is None:
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

def main(source: str):
    generate_frame = GenerateFrameZed(source)
    push_frame = seg.PushFrame()
    for i, image in enumerate(generate_frame()):
        if cv2.waitKey(1) == ord('q'):
            break
        print("Frame count: " + str(i), end="\r")
        push_frame(image)
    push_frame(None)

if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    # if none is provided, use live camera feed
    parser.add_argument('--source', type=str, help='svo path')
    args = parser.parse_args()
    main(source=args.source)
