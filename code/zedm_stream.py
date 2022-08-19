import argparse
import pyzed.sl as sl
from signal import signal, SIGINT
import sys

zed = sl.Camera()

def handler(signal_received, frame):
    zed.close()
    sys.exit(0)

signal(SIGINT, handler)

def main(source: str):
    # Set up parameters
    init_params = sl.InitParameters()
    runtime_params = sl.RuntimeParameters()
    if source is not None:
        init_params.set_from_svo_file(source)
    
    # Initialize camera
    status = zed.open(init_params)
    if status != sl.ERROR_CODE.SUCCESS:
        print(repr(status))
        exit(1)

    # Output frames
    frame_num = 0
    while True:
        status = zed.grab(runtime_params)
        if status == sl.ERROR_CODE.SUCCESS:
            frame_num += 1
            print("Frame count: " + str(frame_num), end="\r")
        elif status == sl.ERROR_CODE.END_OF_SVOFILE_REACHED:
            print("Done")
            exit(1)
        else:
            print("Frame count: " + repr(status))

if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    # if none is provided, use live camera feed
    parser.add_argument('--source', type=str, help='svo path')
    args = parser.parse_args()
    main(source=args.source)
