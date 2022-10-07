import pyzed.sl as sl
from zedm_stream import GenerateFrameZed
import segmentation as seg
import cv2
import time
import numpy as np

# From ZED tutorials
class TimestampHandler:
    def __init__(self):
        self.t_imu = sl.Timestamp()
        self.t_baro = sl.Timestamp()
        self.t_mag = sl.Timestamp()

    # check if the new timestamp is higher than the reference one, and if yes, save the current as reference
    def is_new(self, sensor):
        if (isinstance(sensor, sl.IMUData)):
            new_ = (sensor.timestamp.get_microseconds() > self.t_imu.get_microseconds())
            if new_:
                self.t_imu = sensor.timestamp
            return new_
        elif (isinstance(sensor, sl.MagnetometerData)):
            new_ = (sensor.timestamp.get_microseconds() > self.t_mag.get_microseconds())
            if new_:
                self.t_mag = sensor.timestamp
            return new_
        elif (isinstance(sensor, sl.BarometerData)):
            new_ = (sensor.timestamp.get_microseconds() > self.t_baro.get_microseconds())
            if new_:
                self.t_baro = sensor.timestamp
            return new_


def PositionTracker(zed):
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
        return delta_z, delta_angle_y
    return position_change


def test_position_tracker():
    zed = sl.Camera()
    generate_frame = GenerateFrameZed(zed)
    p = seg.VideoProperties(30, 1920, 1080)
    push_frame = seg.PushFrame((p, "capture.mp4"), "camera")
    position_tracker = PositionTracker(zed)
    for image in generate_frame():
        print(" " * 100, end="\r")
        push_frame(image)
        delta_z, delta_angle_y = position_tracker()
        print(f"Δz: {delta_z}, δy: {delta_angle_y}", end="\r")
        if cv2.waitKey(1) == ord('q'):
            break
    print()
    zed.close()


def main():
    zed = sl.Camera()
    generate_frame = GenerateFrameZed(zed)
    p = seg.VideoProperties(30, 1920, 1080)
    push_frame = seg.PushFrame((p, "capture.mp4"), "camera")
    # initialize positional tracking
    tracking_parameters = sl.PositionalTrackingParameters()
    tracking_parameters.enable_imu_fusion = True
    tracking_parameters.enable_area_memory = True
    # initial_world_transform - tilted camera?
    # enable_area_memory - corrects drift (true)
    # enable_pose_smoothing - smooths pose correction across multiple frames. (Very bugged? Seems to be doing opposite)
    # enable_imu_fusion - true. Only Zed-m uses built in IMU.
    err = zed.enable_positional_tracking(tracking_parameters)
    if err != sl.ERROR_CODE.SUCCESS:
        print("Could not enable positional tracking.")

    zed_pose = sl.Pose()
    zed_transform = sl.Transform()
    print(zed_transform)
    zed_translation = sl.Translation()
    zed_sensors = sl.SensorsData()
    # sensors are sampled at different rates
    ts_handler = TimestampHandler()
    zed_transform_imu = sl.Transform()
    print(zed.get_camera_information().sensors_configuration.barometer_parameters.sampling_rate)
    for i, image in enumerate(generate_frame()):
        # initially some test code to see how camera reference frame works
        #if i % 10 != 0:
        #    continue
        #time.sleep(0.5)
        print(" " * 100, end="\r")
        push_frame(image)
        # positional tracking api
        # camera reference frame tracks change in pose every frame - so can't miss a frame!
        # World is more forgiving, but may be more difficult as have to manage deltas ourselves.
        state = zed.get_position(zed_pose, sl.REFERENCE_FRAME.CAMERA)
        #print(f"State: {state}")
        #print(f"Pose: {zed_pose.pose_data(zed_transform).m}") # Matrix4f
        print(f"State: {state}, Translation: {zed_pose.get_translation(zed_translation).get()}", end="\r")
        #print(f"Euler angles: {zed_pose.get_euler_angles(False)}", end="\r")
        # sensors api
        # may be issue here: https://www.stereolabs.com/docs/api/python/classpyzed_1_1sl_1_1Camera.html#acf9a8efac08c9eef5056e737edb4d62e
        # sl.TIME_REFERENCE.CURRENT not available in SVO.
        # Only certain data at TIME_REFERENCE.IMAGE is available.
        status = zed.get_sensors_data(zed_sensors, sl.TIME_REFERENCE.IMAGE)
        #print(f"Sensors Status: {status}")
        # interesting - zed_sensors.get_temperature_data and zed_sensors.camera_moving_state
        zed_imu = zed_sensors.get_imu_data() # sl.IMUData
        #if ts_handler.is_new(zed_imu):
        zed_imu.get_pose(zed_transform_imu)
        zed_translation_imu = zed_transform_imu.get_translation().get() # sl.Translation
        print(f"IMU Pose: {zed_translation_imu}", end="\r")

        if cv2.waitKey(1) == ord('q'):
            break
    print()
    zed.close()

if __name__ == '__main__':
    main()
    #test_position_tracker()
