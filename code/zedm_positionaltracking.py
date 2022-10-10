import pyzed.sl as sl
from zedm_stream_pointcloud import GenerateFrameZed
import segmentation as seg
import cv2
import time
import numpy as np

def MovementPlotter():
    scale = 2.0 # m / pix
    pix = 800
    scale_to_img = lambda x: np.clip(x / pix / scale + pix / 2, 0, pix - 1).astype(np.int32)
    # super basic class to plot the movement of the wheelchair
    # 1000x1000
    p = seg.VideoProperties(30, pix, pix)
    push_frame = seg.PushFrame((p, "movement.mp4"), "movement")
    pic = np.full((pix, pix, 3), (255, 255, 255), np.uint8)
    def movement_plotter(transform):
        x = scale_to_img(transform[0])
        y = scale_to_img(transform[2])
        pic[x,y] = (0, 0, 0)
        push_frame(pic)
    def end():
        push_frame(None)
    return end, movement_plotter

def PositionTracker(zed):
    # initial_world_transform - tilted camera?
    # enable_area_memory - corrects drift (true)
    # enable_pose_smoothing - smooths pose correction across multiple frames. (Very bugged? Seems to be doing opposite)
    # enable_imu_fusion - true. Only Zed-m uses built in IMU.
    tracking_parameters = sl.PositionalTrackingParameters()
    tracking_parameters.enable_imu_fusion = True # use imu (default)
    tracking_parameters.enable_area_memory = True # use visual odometry (default)
    tracking_parameters.enable_pose_smoothing = False # extremely buggy, terrible results (default)
    err = zed.enable_positional_tracking(tracking_parameters)
    if err != sl.ERROR_CODE.SUCCESS:
        print("Could not enable positional tracking.")
        return None

    w1_inv = sl.Transform() # Initialized as identity matrix. Always in inverted state.
    w2 = sl.Transform() # this is the latest pose
    pose = sl.Pose()

    # This function first calculates the relative movement of the camera in its coord frame, by caching the last world frame.
    # It then operates on the assumption that we can model the wheelchair as a 2d cylindrical robot,
    # with a change in z (movement forward/backward) and change in y-angle (rotation), returning these two values in mm and rad.
    def position_change():
        nonlocal w1_inv
        # REFERENCE_FRAME.CAMERA gets the movement of the camera, in its reference frame, since the last call to zed.grab(params)
        # The following algorithm reliably returns a position change when no frames are skipped - e.g. actual camera, svo real time, or frame-by-frame.
        # However, issues will arise if frames are skipped - for example, non real time smoothing.
        # To avoid this, can we generate our own CAMERA frame from two WORLD frames, so we don't rely on zed.grab?
        # Lets go back to basic math - two world pose matricies W1 and W2, and we want to find the camera pose matrix C.
        # W2 = W1 * C (post-multiplication for local coordinate frame) => C = W1 ^ -1 * W2
        # Lets see how fast matrix inversion is at the moment.
        # This algorithm can be sped up by assuming small angles - then all we need is pythagoras to calculate delta-z and euler angles for delta-angle-y.
        # But it is likely somewhere else will be slower.
        # ^^ Take that back, inverting a Pose matrix is very very fast

        # Get the camera coordinate
        state = zed.get_position(pose, sl.REFERENCE_FRAME.WORLD)
        pose.pose_data(w2)
        c = w1_inv * w2 # stereolabs api defines matmul for transforms with '*'
        # Timestep
        w1_inv = sl.Transform()
        w1_inv.init_transform(w2) # prevent aliasing
        w1_inv.inverse() # this returns SUCCESS
        # Extract parameters
        delta_z = c[2, 3]
        ct = sl.Transform()
        ct.init_matrix(c) # get_euler_angles requires transform, not matrix4f
        delta_angle_y = ct.get_euler_angles()[1]
        return delta_z, delta_angle_y, w2.get_translation().get()
    return position_change


def test_position_tracker():
    end, plotter = MovementPlotter()
    zed = sl.Camera()
    generate_frame = GenerateFrameZed(zed)
    p = seg.VideoProperties(30, 1920, 1080)
    push_frame = seg.PushFrame((p, "capture.mp4"), "camera")
    position_tracker = PositionTracker(zed)
    for image in generate_frame():
        print(" " * 100, end="\r")
        image_rgb = np.delete(image, 3, 2)
        push_frame(image_rgb)
        delta_z, delta_angle_y, trans = position_tracker()
        print(f"Δz: {delta_z}, δy: {delta_angle_y}, Trans (abs): {trans}", end="\r")
        plotter(trans)
        if cv2.waitKey(1) == ord('q'):
            break
    zed.close()
    push_frame(None)
    end()

if __name__ == '__main__':
    test_position_tracker()
