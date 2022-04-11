import cv2
import argparse
import time

def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('--source', type=str, help='video path')
    args = parser.parse_args()
    print(f"Video source: {args.source}")
    vid = cv2.VideoCapture(args.source)
    if not vid.isOpened():
        return
    fps, width, height = vid.get(cv2.CAP_PROP_FPS), int(vid.get(cv2.CAP_PROP_FRAME_WIDTH)), int(vid.get(cv2.CAP_PROP_FRAME_HEIGHT))
    print(f"Video Properties:\nfps {fps} resolution {width},{height}")
    fourcc = cv2.VideoWriter_fourcc(*'H264')
    output = cv2.VideoWriter('test.mp4', fourcc, fps, (width,  height))
    while True:
        success, frame = vid.read()
        # press q to exit
        if not success or cv2.waitKey(1) == ord('q'):
            break
        cv2.imshow('frame', frame)
        output.write(frame)
    vid.release()
    output.release()
    cv2.destroyAllWindows()

if __name__ == '__main__':
    main()
