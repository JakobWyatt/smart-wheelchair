# smart-wheelchair
My Curtin University Mechatronics Engineering Honours thesis project -
Navigation assistance for a semi-autonomous smart wheelchair.

Abstract:
Semi-autonomous smart wheelchair technology can enable visually impaired users to drive a wheelchair
safely. In collaboration with wheelchair manufacturer Glide, a navigation assistance system for a
smart wheelchair is implemented and evaluated. This smart wheelchair uses a CentroGlide wheelchair
as a powered base and a ZED Mini RGB-D stereo camera to detect the surrounding environment.
A semantic segmentation ML model was retrained to identify footpaths and other drivable areas around the wheelchair.
Additionally, an algorithm was developed to identify obstacles and hazards using 3D point cloud data from the stereo camera.
A birds-eye view occupancy map is generated to indicate the location of obstacles and drivable areas
around the wheelchair. This occupancy map is used to determine a safe target direction for the wheelchair.
To evaluate this navigation assistance system, an RGB-D wheelchair driving dataset was collected
around Curtin University. It was found that the identification of drivable areas using semantic segmentation was effective in outdoor
areas but less effective indoors. Obstacle detection was effective at identifying environmental obstacles such as
walls and handrails. The assistive control algorithm successfully modifies the wheelchair's direction to avoid obstacles,
however, can fail in some scenarios due to the low FOV of the stereo camera. Suggestions for future work are also discussed.
