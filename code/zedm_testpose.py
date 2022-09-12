import pyzed.sl as sl
from zedm_stream import GenerateFrameZed
import segmentation as seg
import cv2

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
    zed_translation = sl.Translation()
    zed_sensors = sl.SensorsData()
    # sensors are sampled at different rates
    ts_handler = TimestampHandler()
    zed_transform_imu = sl.Transform()
    for i, image in enumerate(generate_frame()):
        if i % 5 != 0:
            continue
        print(" " * 100, end="\r")
        push_frame(image)
        # positional tracking api
        # camera reference frame tracks change in pose every frame - so can't miss a frame!
        # World is more forgiving, but may be more difficult as have to manage deltas ourselves.
        state = zed.get_position(zed_pose, sl.REFERENCE_FRAME.WORLD)
        #print(f"State: {state}")
        #print(f"Pose: {zed_pose.pose_data(zed_transform).m}") # Matrix4f
        #print(f"State: {state}, Translation: {zed_pose.get_translation(zed_translation).get()}", end="\r")
        print(f"Euler angles: {zed_pose.get_euler_angles(False)}", end="\r")
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
        #print(f"IMU Pose: {zed_translation_imu}", end="\r")

        if cv2.waitKey(1) == ord('q'):
            break
    print()
    zed.close()

if __name__ == '__main__':
    main()
