function [steerDir, retvfh, scan, binmap] = vfhControllerCoder(pose, inputDir, map)
    persistent vfh lidar range
    if isempty(range)
        range = [0 15];
    end
    if isempty(vfh)
        vfh = controllerVFH('UseLidarScan', true, "SafetyDistance", 1.0, "DistanceLimits", range, "HistogramThresholds", [100 200], "MinTurningRadius", 1.0, "TargetDirectionWeight", 5.0);
    end
    if isempty(lidar)
        lidar = rangeSensor("Range", range);
    end

    binmap = binaryOccupancyMap(map);
    [ranges, angles] = lidar(pose, binmap);
    scan = lidarScan(ranges, angles);
    steerDir = vfh(scan, inputDir);
    retvfh = vfh;
end
