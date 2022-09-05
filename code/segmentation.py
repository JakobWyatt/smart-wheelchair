from concurrent.futures import process
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
device = 'cuda' if torch.cuda.is_available() else 'cpu'

def GenerateFrameVideo(path):
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

# If fn is None only display image
# fn is a tuple of (video properties, file name)
def PushFrame(fn: str = None, name: str = "frame", flag = cv2.WINDOW_NORMAL):
    #if platform.system() == "Darwin":
    if fn is not None:
        p = fn[0]
        fourcc = cv2.VideoWriter_fourcc(*'mp4v')
        print(f"Video Properties:\nfps {p.fps} resolution {p.width},{p.height}")
        output = cv2.VideoWriter(fn[1], fourcc, p.fps, (p.width,  p.height))
    cv2.namedWindow(name, flag)
    def push_frame(frame):
        if frame is None:
            cv2.destroyAllWindows()
            if fn is not None:
                output.release()
        else:
            cv2.imshow(name, frame)
            if fn is not None:
                output.write(frame)
    return push_frame

def HybridnetLoader(p, path = None):
    import sys
    from pathlib import Path
    hybridnetspath = Path("../repositories/HybridNets")
    sys.path.insert(0, str(hybridnetspath))
    from backbone import HybridNetsBackbone
    from utils.utils import Params
    from utils.constants import BINARY_MODE
    params = Params(str(hybridnetspath / "projects" / "bdd100k.yml"))

    if path is None:
        model = torch.hub.load('datvuthanh/hybridnets', 'hybridnets', pretrained=True, device=device)
    else:
        # Create a model without lane detection
        model = HybridNetsBackbone(num_classes=len(params.obj_list), compound_coef=3,
                               ratios=eval(params.anchors_ratios), scales=eval(params.anchors_scales),
                               seg_mode=BINARY_MODE, backbone_name=None)
        model.load_state_dict(torch.load(path)['model'])
        model = model.to(device)
    model.eval()
    process_frame = ProcessFrameHybrid(p, model, path is not None)
    return process_frame

def ProcessFrameHybrid(p, model, is_binary = False):
    # Using 128 here is a weird hack - signed vs unsigned??
    colors = np.array([[0, 0, 0], [0, 128, 0], [0, 0, 128]], dtype=np.uint8)

    preprocess_tensor = torchvision.transforms.Compose([
        torchvision.transforms.ToTensor(),
        torchvision.transforms.Normalize(mean=[0.485, 0.456, 0.406], std=[0.229, 0.224, 0.225]),
    ])

    def preprocess_frame(frame):
        frame = cv2.resize(cv2.cvtColor(frame, cv2.COLOR_BGR2RGB), (640, 384), interpolation=cv2.INTER_AREA)
        frame = preprocess_tensor(frame).unsqueeze(0)
        return frame.to(device)

    def postprocess_frame(seg):
        if is_binary:
            seg_mask = seg[0].round().squeeze(0).byte().cpu().numpy()
        else:
            seg_mask = seg[0].argmax(0).byte().cpu().numpy()
        seg_mask = PIL.Image.fromarray(seg_mask)
        seg_mask = seg_mask.resize((p.width, p.height))
        seg_mask = np.array(seg_mask, dtype=np.uint8)
        return seg_mask

    def draw_frame(frame, seg_mask):
        seg_mask = PIL.Image.fromarray(seg_mask)
        seg_mask.putpalette(colors)
        seg_mask = seg_mask.convert("RGB")
        seg_mask = np.array(seg_mask, dtype=np.uint8)
        cv2.addWeighted(frame, 1, seg_mask, 0.8, 0, frame)
        return frame

    def process_frame(frame):
        # opencv: 2d array, linear pixels, bgr, 0-255
        model_input = preprocess_frame(frame)
        with torch.no_grad():
            # focus on segmentation for now
            features, regression, classification, anchors, segmentation = model(model_input)
        return postprocess_frame(segmentation)
    return process_frame, draw_frame

def ProcessFrameDeeplab(p):
    # resnet50 resnet101 mobilenet_v3_large
    seg_model = torch.hub.load('pytorch/vision:v0.10.0', 'deeplabv3_mobilenet_v3_large', pretrained=True)
    seg_model.eval()
    seg_model.to(device)
    
    colors = np.random.randint(256, size=(21, 3), dtype=np.uint8)
    colors[0] = [0, 0, 0]

    preprocess_tensor = torchvision.transforms.Compose([
        torchvision.transforms.ToTensor(),
        torchvision.transforms.Normalize(mean=[0.485, 0.456, 0.406], std=[0.229, 0.224, 0.225]),
    ])
    def preprocess_frame(frame):
        factor = 0.5
        frame = cv2.resize(cv2.cvtColor(frame, cv2.COLOR_BGR2RGB), (0, 0), fx=factor, fy=factor)
        frame = preprocess_tensor(frame).unsqueeze(0)
        frame.to(device)
        return frame

    def postprocess_frame(frame, pred):
        pred = PIL.Image.fromarray(pred)
        pred.putpalette(colors)
        pred = pred.resize((p.width, p.height)).convert("RGB")
        pred = np.array(pred)
        cv2.addWeighted(frame, 1, pred, 0.8, 0, frame)
        return frame

    def process_frame(frame):
        # segmentation
        # opencv: 2d array, linear pixels, bgr, 0-255
        model_input = preprocess_frame(frame)
        with torch.no_grad():
            output = seg_model(model_input)
        output_predictions = output['out'][0].argmax(0).byte().cpu().numpy()
        #stacked = np.vstack((detected, postprocess_frame(output_predictions)))
        return postprocess_frame(frame, output_predictions)
    return process_frame

def ProcessFrameYolo(p):
    # nsmlx
    yolo = torch.hub.load('ultralytics/yolov5', 'yolov5s')
    def process_frame(frame):
        output = yolo(frame)
        output.render()
        return output.imgs[0]

def main(*, source: str, drop_frames: bool, model: str, weights: str):
    generate_frame, p = GenerateFrameVideo(source)
    if generate_frame is not None:
        push_frame = PushFrame((p, "test.mp4"))
        if model == 'hybridnets':
            model, draw_frame = HybridnetLoader(p, weights)
            process_frame = lambda x: draw_frame(x, model(x))
        elif model == 'deeplab':
            process_frame = ProcessFrameDeeplab(p)
        elif model == 'yolo':
            process_frame = ProcessFrameYolo(p)
        else:
            print("INVALID MODEL NAME")
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
    print("Available GPUs:")
    print(torch.cuda.get_device_properties(device))
    print(torch.cuda.memory_summary())
    parser = argparse.ArgumentParser()
    parser.add_argument('--drop-frames', action=argparse.BooleanOptionalAction, help="drop frames for low latency")
    parser.add_argument('--source', type=str, help='video path')
    parser.add_argument('--model', type=str, help='model to use')
    parser.add_argument('--weights', type=str, help='path to model weights')
    args = parser.parse_args()
    main(source=args.source, drop_frames=args.drop_frames, model=args.model, weights=args.weights)
