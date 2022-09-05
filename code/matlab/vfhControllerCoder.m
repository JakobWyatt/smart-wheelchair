function [steerDir, vfh, scan, binmap] = vfhControllerCoder(pose, map, inputDir)
    binmap = binaryOccupancyMap(map);
    lidar = rangeSensor("Range", [0 15]);
    [ranges, angles] = lidar(pose, binmap);
    scan = lidarScan(ranges, angles);
    vfh = controllerVFH('UseLidarScan', true, "SafetyDistance", 1.0, "DistanceLimits", lidar.Range, "HistogramThresholds", [100 200], "MinTurningRadius", 1.0, "TargetDirectionWeight", 5.0);
    steerDir = vfh(scan, inputDir);
end
