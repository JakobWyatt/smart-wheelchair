import cv2
import torch
import torchvision
import PIL
import numpy as np

import argparse
import platform

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
                return
            yield frame
    return generate_frame, vid

def PushFrame(vid):
    fps, width, height = vid.get(cv2.CAP_PROP_FPS), int(vid.get(cv2.CAP_PROP_FRAME_WIDTH)), int(vid.get(cv2.CAP_PROP_FRAME_HEIGHT))
    print(f"Video Properties:\nfps {fps} resolution {width},{height}")
    if platform.system() == "Darwin":
        fourcc = cv2.VideoWriter_fourcc(*'X264')
        extension = 'mkv'
    else:
        fourcc = cv2.VideoWriter_fourcc(*'H264')
        extension = 'mp4'
    output = cv2.VideoWriter(f'test.{extension}', fourcc, fps, (width,  height))
    def push_frame(frame):
        if frame is None:
            vid.release()
            output.release()
            cv2.destroyAllWindows()
        else:
            cv2.imshow('frame', frame)
            output.write(frame)
    return push_frame

def ProcessFrame():
    model = torch.hub.load('pytorch/vision:v0.10.0', 'deeplabv3_resnet50', pretrained=True)
    model.eval()
    if torch.cuda.is_available():
        model.to('cuda')
    
    colors = np.random.randint(256, size=(3, 21))
    preprocess_tensor = torchvision.transforms.Compose([
        torchvision.transforms.ToTensor(),
        torchvision.transforms.Normalize(mean=[0.485, 0.456, 0.406], std=[0.229, 0.224, 0.225]),
    ])
    def preprocess_frame(frame):
        frame = preprocess_tensor(
            cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
        ).unsqueeze(0)
        if torch.cuda.is_available():
            return frame.to('cuda')
        return frame
    
    def process_frame(frame):
        # opencv: 2d array, linear pixels, bgr, 0-255
        model_input = preprocess_frame(frame)
        with torch.no_grad():
            output = model(model_input)
        output_predictions = output['out'][0].argmax(0).byte().cpu().numpy()
        segmented = PIL.Image.fromarray(output_predictions)
        segmented.putpalette(colors)
        return np.array(segmented)
    return process_frame

def main(*, source: str):
    generate_frame, vid = GenerateFrame(source)
    if generate_frame is not None:
        push_frame = PushFrame(vid)
        process_frame = ProcessFrame()
        for frame in generate_frame():
            new_frame = process_frame(frame)
            push_frame(new_frame)
        push_frame(None) # cleanup

if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument('--source', type=str, help='video path')
    args = parser.parse_args()
    main(source=args.source)
