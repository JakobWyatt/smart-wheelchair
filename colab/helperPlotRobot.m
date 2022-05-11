% MATLAB Example Code
function robotHandle = helperPlotRobot(ax, pose, scale)
    if nargin < 3
        scale = 0.5;
    end
    % Update robot position
    t = pose(1:2);
    a = pose(3);
    R = [cos(a) -sin(a); sin(a) cos(a)];
    G = [R t(:); 0 0 scale];
    
    RobotBodyTriangleVertices = G*[[[-0.3, -0.05,-0.3, 0.8]; [-0.5,0,0.5,0]]; ones(1,4)];
    RobotBodyFaceColor = [0.866 0.918 0.753];
    
    robotHandle = patch(ax, RobotBodyTriangleVertices(1,:), RobotBodyTriangleVertices(2,:), RobotBodyFaceColor);
end