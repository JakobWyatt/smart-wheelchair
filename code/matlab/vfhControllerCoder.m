function [steerDir, retvfh, scan, binmap] = vfhControllerCoder(pose, inputDir, map, resolution)
    persistent vfh lidar range vfhfig otherfig
    WHEELCHAIR_WIDTH = 0.70;
    if isempty(range)
        range = [0.1 15];
    end
    if isempty(vfh)
        vfh = controllerVFH('UseLidarScan', true, ...
            "RobotRadius", WHEELCHAIR_WIDTH / 2, ...
            "SafetyDistance", 0.20, ...
            "DistanceLimits", range, ...
            "HistogramThresholds", [100 200], ...
            "MinTurningRadius", 0.5);
    end
    if isempty(lidar)
        lidar = rangeSensor("Range", range, "HorizontalAngleResolution", 0.005);
    end
    if isempty(vfhfig)
        vfhfig = figure;
    end
    if isempty(otherfig)
        otherfig = figure;
    end
    % pose is of camera
    % we want to shift to centre of wheelchair
    % change x value
    pose(1) = pose(1) - WHEELCHAIR_WIDTH / 2;
    binmap = binaryOccupancyMap(map, resolution);
    [ranges, angles] = lidar(pose, binmap);
    scan = lidarScan(ranges, angles);
    steerDir = vfh(scan, inputDir);
    retvfh = vfh;

    figure(vfhfig);
    show(vfh);
    figure(otherfig);
    subplot(1, 2, 1);
    show(binmap);
    subplot(1, 2, 2);
    plot(scan);
    xlim([0 15]);
    ylim([-5 5]);
end
