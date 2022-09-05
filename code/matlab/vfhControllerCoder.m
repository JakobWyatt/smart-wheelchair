% MATLAB Example Code
function steerDir = vfhControllerCoder(pose, map)
    binmap = binaryOccupancyMap(map);
    lidar = rangeSensor("Range", [0 15]);
    [ranges, angles] = lidar(pose, binmap);
    scan = lidarScan(ranges, angles);
    vfh = controllerVFH('UseLidarScan', true);
    vfh.SafetyDistance = 1.0;
    vfh.DistanceLimits = lidar.Range;
    vfh.HistogramThresholds = [100 200];
    vfh.MinTurningRadius = 1.0;
    vfh.TargetDirectionWeight = 5.0;
    steerDir = vfh(scan, -pi / 2);
end
