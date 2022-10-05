import matplotlib.pyplot as plt
import matlab.engine
import math
from scipy.io import loadmat
import numpy as np
import time

def test1():
    # Adds ./matlab to path
    eng = matlab.engine.start_matlab(option="-sd ./matlab")
    #vfh = eng.controllerVFH('UseLidarScan', True)

    pose = matlab.double(np.array([4, 4, 0], dtype=np.double))
    inputDir = matlab.double(-math.pi / 2)
    mapmat = matlab.logical(loadmat("matlab/occupancy.mat")['mapmat'])

    steerDir, vfh = eng.vfhControllerCoder(pose, inputDir, mapmat, nargout=2)
    print(steerDir)
    eng.show(vfh)

    #plt.plot(0, 0, 'bo')
    #plt.show()
    input("Press Enter to continue...")

def test2():
    eng = matlab.engine.start_matlab(option="-sd ./matlab")
    pose = matlab.double(np.array([4, 4, 0], dtype=np.double))
    inputDir = matlab.double(-math.pi / 2)
    mapmat = matlab.logical(loadmat("matlab/occupancy.mat")['mapmat'])
    start_time = time.time()
    for _ in range(100):
        steerDir, vfh, scan, binmap, vfhfig, otherfig = eng.vfhControllerCoder(pose, 0.0, mapmat, 1.0, nargout=6)
    elapsed_time = time.time() - start_time
    print(elapsed_time)

if __name__ == '__main__':
    test2()
