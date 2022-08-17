import matplotlib.pyplot as plt
import matlab.engine

if __name__ == '__main__':
    eng = matlab.engine.start_matlab()
    vfh = eng.controllerVFH('UseLidarScan', True)
    plt.plot(0, 0, 'bo')
    plt.show()
