import cv2
import torch
import torchvision
import PIL
import numpy as np
import matplotlib.pyplot as plt

import argparse
import platform
from collections import namedtuple
import time
import math

VideoProperties = namedtuple('VideoProperties', ['fps', 'width', 'height'])

def GenerateFrame(path):
    print(f"Video source: {path}")
    vid = cv2.VideoCapture(path)
    if not vid.isOpened():
        return None, None
    def generate_frame():
        while True:
            success, frame = vid.read()
            # press q to exit
            if not success or cv2.waitKey(1) == ord('q'):
                vid.release()
                return
            yield frame
    properties = VideoProperties(vid.get(cv2.CAP_PROP_FPS), int(vid.get(cv2.CAP_PROP_FRAME_WIDTH)), int(vid.get(cv2.CAP_PROP_FRAME_HEIGHT)))
    return generate_frame, properties

def PushFrame(p):
    print(f"Video Properties:\nfps {p.fps} resolution {p.width},{p.height}")
    fourcc = cv2.VideoWriter_fourcc(*'mp4v')
    if platform.system() == "Darwin":
        print("No GPU")
    output = cv2.VideoWriter(f'test.mp4', fourcc, p.fps, (p.width,  p.height))
    cv2.namedWindow('frame', cv2.WINDOW_NORMAL)
    def push_frame(frame):
        if frame is None:
            output.release()
            cv2.destroyAllWindows()
        else:
            cv2.imshow('frame', frame)
            output.write(frame)
    return push_frame

def ProcessFrame(p):
    model = torch.hub.load('pytorch/vision:v0.10.0', 'deeplabv3_resnet50', pretrained=True)
    model.eval()
    if torch.cuda.is_available():
        model.to('cuda')
    
    colors = np.random.randint(256, size=(21, 3), dtype=np.uint8)
    colors[0] = [0, 0, 0]

    preprocess_tensor = torchvision.transforms.Compose([
        torchvision.transforms.ToTensor(),
        torchvision.transforms.Normalize(mean=[0.485, 0.456, 0.406], std=[0.229, 0.224, 0.225]),
    ])
    def preprocess_frame(frame):
        factor = 0.3
        frame = cv2.resize(cv2.cvtColor(frame, cv2.COLOR_BGR2RGB), (0, 0), fx=factor, fy=factor)
        frame = preprocess_tensor(frame).unsqueeze(0)
        if torch.cuda.is_available():
            return frame.to('cuda')
        return frame

    def postprocess_frame(frame):
        frame = PIL.Image.fromarray(frame)
        frame.putpalette(colors)
        frame = frame.resize((p.width, p.height)).convert("RGB")
        return np.array(frame)
    
    def process_frame(frame):
        # opencv: 2d array, linear pixels, bgr, 0-255
        model_input = preprocess_frame(frame)
        with torch.no_grad():
            output = model(model_input)
        output_predictions = output['out'][0].argmax(0).byte().cpu().numpy()
        return np.vstack((frame, postprocess_frame(output_predictions)))
    return process_frame

def main(*, source: str, drop_frames: bool):
    generate_frame, p = GenerateFrame(source)
    if generate_frame is not None:
        push_frame = PushFrame(p)
        process_frame = ProcessFrame(p)
        frames_drop = 0
        for frame in generate_frame():
            if frames_drop == 0:
                start_time = time.time()
                new_frame = process_frame(frame)
                push_frame(new_frame)
                elapsed = time.time() - start_time
                print(f"Current FPS: {1 / elapsed}")
                if drop_frames:
                    frames_drop = math.ceil(elapsed * p.fps) - 1
            else:
                frames_drop -= 1
        push_frame(None) # cleanup

if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument('--drop-frames', action=argparse.BooleanOptionalAction, help="drop frames for low latency")
    parser.add_argument('--source', type=str, help='video path')
    args = parser.parse_args()
    main(source=args.source, drop_frames=args.drop_frames)