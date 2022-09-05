import matplotlib.pyplot as plt
import matlab.engine
import math
from scipy.io import loadmat

if __name__ == '__main__':
    eng = matlab.engine.start_matlab(option="-sd ./matlab")
    #vfh = eng.controllerVFH('UseLidarScan', True)

    pose = matlab.double([4, 4, 0])
    inputDir = matlab.double(-math.pi / 2)
    mapmat = matlab.logical(loadmat("matlab/occupancy.mat")['mapmat'])

    steerDir, vfh = eng.vfhControllerCoder(pose, inputDir, mapmat, nargout=2)
    print(steerDir)
    eng.show(vfh)

    #plt.plot(0, 0, 'bo')
    #plt.show()
    input("Press Enter to continue...")
