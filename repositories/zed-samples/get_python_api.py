import os
import platform
import sys
import re
import urllib.request
import argparse
from pathlib import Path
import subprocess
import sys
import math
import shutil

ZED_SDK_MAJOR = ""
ZED_SDK_MINOR = ""

CUDA_MAJOR_ZED = ""
CUDA_MINOR_ZED = ""

CUDA_STR = ""

CUDA_MAJOR = "?"
CUDA_MINOR = "?"

PYTHON_MAJOR = ""
PYTHON_MINOR = ""

OS_VERSION = ""
CUDA_INDEPENDANT_VERSION=False
ARCH_VERSION = platform.machine()

whl_platform_str = ""

cuda_path = "/usr/local/cuda"
base_URL = "http://download.stereolabs.com/zedsdk/"

def pip_install(package, force_install=False):
    try:
        call_list=[sys.executable, "-m", "pip", "install"]
        if force_install:
            call_list.append("--ignore-installed")
        call_list.append(package)
        err = subprocess.check_call(call_list)
    except Exception as e:
        err = 1
        #print("DEBUG : Exception " + str(e))
    #print("DEBUG : " + package + " errcode " + str(err))
    return err

def check_valid_file(file_path):
    file_size = os.stat(file_path).st_size / 1000.
    # size > 150 Ko
    return (file_size > 150)

def install_win_dep(name, py_vers):
    whl_file = name + "-3.1.5-cp" + str(py_vers) +"-cp" + str(py_vers)
    if py_vers <= 37:
        whl_file = whl_file +"m"
    if py_vers >= 310:
        whl_file = name + "-3.1.6-cp" + str(py_vers) +"-cp" + str(py_vers)
    whl_file = whl_file +"-win_amd64.whl"

    whl_file_URL = "http://download.stereolabs.com/py/"+whl_file
    print("-> Downloading "+ whl_file)
    whl_file = os.path.join(dirname, whl_file)
    urllib.request.urlretrieve(whl_file_URL, whl_file)
    pip_install(whl_file)

def get_pyzed_directory():
    try:
        call_list=[sys.executable, "-m", "pip", "show", "pyzed"]
        lines = subprocess.check_output(call_list).decode().splitlines()
        for line in lines:
            words = line.split()
            if(len(words) >= 2):
                if(words[0] == "Location:"):
                    if(os.path.isdir(words[1])):
                        print("Pyzed directory is " + words[1])
                        return words[1]+"/pyzed"
                    else:
                        print("ERROR : not a directory")
            
        print("ERROR : Unable to find pyzed installation folder")
        print(lines)

    except Exception as e:
        print("ERROR : Unable to find pyzed installation folder.")
        return ""

def check_cuda_version(cuda_path_version):
    global CUDA_STR
    global CUDA_MAJOR
    global CUDA_MINOR

    try:
        with open(cuda_path_version, "r", encoding="utf-8") as myfile:
            data = myfile.read()
            p = re.compile("CUDA Version (.*)")
            CUDA_VERSION = p.search(data).group(1)
            temp = re.findall(r'\d+', CUDA_VERSION)
            res = list(map(int, temp))
            CUDA_MAJOR = int(res[0])
            CUDA_MINOR = int(res[1])
            #print("CUDA " + str(CUDA_MAJOR) + "." + str(CUDA_MINOR))
            CUDA_STR = "cu" + str(CUDA_MAJOR) + str(CUDA_MINOR)
    except FileNotFoundError:
        # Version.txt doesn't exist, check the var itself
        try:
            temp = re.findall(r'\d+', cuda_path_version)
            CUDA_MAJOR = int(temp[0])
            CUDA_MINOR = int(temp[1])
            #print("CUDA: " + str(CUDA_MAJOR) + "." + str(CUDA_MINOR))
            CUDA_STR = "cu" + str(CUDA_MAJOR) + str(CUDA_MINOR)
        except IndexError:
            # Version not in the path either, check nvcc output
            if "linux" in sys.platform:
                cuda_path = cuda_path_version.replace('version.txt', '')
                cmd = cuda_path + "bin/nvcc --version | egrep -o 'V[0-9]+.[0-9]'"
                try:
                    output = subprocess.check_output(cmd, shell=True).decode("utf-8").replace('\n', '')
                    temp = re.findall(r'\d+', output)
                    CUDA_MAJOR = int(temp[0])
                    CUDA_MINOR = int(temp[1])
                    CUDA_STR = "cu" + str(CUDA_MAJOR) + str(CUDA_MINOR)
                except:# subprocess.CalledProcessError:
                    print("nvcc not available, failed to find the CUDA version installed")
            else:
                raise NotImplementedError

def check_zed_sdk_version_private(file_path):
    global ZED_SDK_MAJOR
    global ZED_SDK_MINOR
    global CUDA_INDEPENDANT_VERSION

    with open(file_path, "r", encoding="utf-8") as myfile:
        data = myfile.read()

    p = re.compile("ZED_SDK_MAJOR_VERSION (.*)")
    ZED_SDK_MAJOR = p.search(data).group(1)

    p = re.compile("ZED_SDK_MINOR_VERSION (.*)")
    ZED_SDK_MINOR = p.search(data).group(1)
    if not (int(ZED_SDK_MAJOR) > 3 or (int(ZED_SDK_MAJOR) == 3 and int(ZED_SDK_MINOR) < 6)):
        CUDA_INDEPENDANT_VERSION = True

def check_zed_sdk_version(file_path):
    file_path_ = file_path+"/sl/Camera.hpp"
    try:
        check_zed_sdk_version_private(file_path_)
    except AttributeError:
        file_path_ = file_path+"/sl_zed/defines.hpp"
        check_zed_sdk_version_private(file_path_)

def check_zed_sdk_cuda_version(file_path):
    global CUDA_MAJOR_ZED
    global CUDA_MINOR_ZED

    with open(file_path+"/zed-config.cmake", "r", encoding="utf-8") as myfile:
        data = myfile.read()
    temp=re.findall("ZED_CUDA_VERSION (.*)",data)

    b= ""
    for b in temp:
        results=re.findall("\d", b)
        if(results):
            break
    x = re.split("\.", b[:-1])
    CUDA_MAJOR_ZED = int(x[0])
    try:
        CUDA_MINOR_ZED = int(x[1])
    except IndexError:
        CUDA_MINOR_ZED = 0 # Default to 0 if not found

parser = argparse.ArgumentParser(description='Helper script to download and setup the ZED Python API')
parser.add_argument('--path', help='whl file destination path')
args = parser.parse_args()

arch = platform.architecture()[0]
if arch != "64bit":
    print("ERROR : Python 64bit must be used, found " + str(arch))
    sys.exit(1)

# If path empty, take pwd
dirname = args.path or os.getcwd()

# If no write access, download in home
if not (os.path.exists(dirname) and os.path.isdir(dirname) and os.access(dirname, os.W_OK)):
    dirname = str(Path.home())

print("-> Downloading to '" + str(dirname) + "'")

if sys.platform == "win32":
    zed_path = os.getenv("ZED_SDK_ROOT_DIR")
    if zed_path is None:
        print("Error: you must install the ZED SDK.")
        sys.exit(1)
    elif os.getenv("CUDA_PATH") is None:
        print("Error: you must install Cuda.")
        sys.exit(1)
    else:
        check_zed_sdk_version(zed_path+"/include")
        cuda_path_version = os.getenv("CUDA_PATH") + "/version.txt"
    OS_VERSION = "win"
    whl_platform_str = "win"
    if not CUDA_INDEPENDANT_VERSION:
        check_cuda_version(cuda_path_version)
        check_zed_sdk_cuda_version(zed_path)

elif "linux" in sys.platform:

    if "aarch64" in ARCH_VERSION:
        with open("/etc/nv_tegra_release", "r", encoding="utf-8") as myfile:
            data = myfile.read()
        number_extraction = re.findall(r'\d+', data)
        TEGRA_RELEASE_MAJOR = int(number_extraction[0])
        TEGRA_RELEASE_MINOR = int(number_extraction[1])
        TEGRA_RELEASE_PATCH = int(number_extraction[2])

        #TEGRA_RELEASE = str(TEGRA_RELEASE_MAJOR) + "." + str(TEGRA_RELEASE_MINOR) + "." + str(TEGRA_RELEASE_PATCH)
        #print(TEGRA_RELEASE)
        if ZED_SDK_MAJOR == 3 and ZED_SDK_MINOR < 7:
            if TEGRA_RELEASE_MAJOR < 32:
                print('Unsupported jetpack version')
                sys.exit(1)
            elif TEGRA_RELEASE_MAJOR == 32:
                if TEGRA_RELEASE_MINOR == 2:
                    JETSON_JETPACK="42"
                elif TEGRA_RELEASE_MINOR == 3:
                    JETSON_JETPACK="43"
                elif TEGRA_RELEASE_MINOR == 4:
                    JETSON_JETPACK="44"
                elif TEGRA_RELEASE_MINOR == 5:
                    JETSON_JETPACK="45"
                elif TEGRA_RELEASE_MINOR == 6:
                    JETSON_JETPACK="46"
                #elif TEGRA_RELEASE_MINOR == 7:
                #    JETSON_JETPACK="461"
                else:
                    print('Unsupported jetpack version')
                    sys.exit(1)
            else:
                print('Unsupported jetpack version')
                sys.exit(1)
            print("JETPACK " + str(JETSON_JETPACK))
            CUDA_STR = "jp" + JETSON_JETPACK
        else: # 3.7 handle jetson with the Linux4Tegra version instead of jetpack version
            if TEGRA_RELEASE_MAJOR < 32:
                print('Unsupported l4t/jetpack version')
                sys.exit(1)
            print("L4T " + str(TEGRA_RELEASE_MAJOR) + "." + str(TEGRA_RELEASE_MINOR))
            CUDA_STR = "l4t" + str(TEGRA_RELEASE_MAJOR)# + "." + str(TEGRA_RELEASE_MINOR)
            OS_VERSION = "jetsons"
    else:
        with open("/etc/lsb-release", "r", encoding="utf-8") as myfile:
            data = myfile.read()
        p = re.compile("DISTRIB_RELEASE=(.*)")
        DISTRIB_RELEASE = p.search(data).group(1).split(".")[0]
        p = re.compile("DISTRIB_ID=(.*)")
        DISTRIB_ID = p.search(data).group(1).lower()
        OS_VERSION = DISTRIB_ID + DISTRIB_RELEASE

        if not os.path.isdir(cuda_path):
            print("Error: you must install Cuda.")
            sys.exit(1)
        cuda_path_version = cuda_path + "/version.txt"
        check_cuda_version(cuda_path_version)

    zed_path = "/usr/local/zed"
    if not os.path.isdir(zed_path):
        print("Error: you must install the ZED SDK.")
        sys.exit(1)
    check_zed_sdk_version(zed_path+"/include")
    whl_platform_str = "linux"
    if not CUDA_INDEPENDANT_VERSION:
        check_zed_sdk_cuda_version(zed_path)
else:
    print ("Unknown system.platform: %s  Installation failed, see setup.py." % sys.platform)
    sys.exit(1)

PYTHON_MAJOR = platform.python_version().split(".")[0]
PYTHON_MINOR = platform.python_version().split(".")[1]

whl_python_version = "-cp" + str(PYTHON_MAJOR) + str(PYTHON_MINOR) + "-cp" + str(PYTHON_MAJOR) + str(PYTHON_MINOR)
if int(PYTHON_MINOR) < 8 :
    whl_python_version += "m"

disp_str = "Detected platform: \n\t " + str(OS_VERSION) + "\n\t Python " + str(PYTHON_MAJOR) + "." + str(PYTHON_MINOR)
if "aarch64" not in ARCH_VERSION and not CUDA_INDEPENDANT_VERSION:
    disp_str += "\n\t CUDA " + str(CUDA_MAJOR) + "." + str(CUDA_MINOR)
disp_str += "\n\t ZED SDK " + str(ZED_SDK_MAJOR) + "." + str(ZED_SDK_MINOR)
if "aarch64" not in ARCH_VERSION and not CUDA_INDEPENDANT_VERSION:
    disp_str += " (requiring CUDA " + str(CUDA_MAJOR_ZED) + "." + str(CUDA_MINOR_ZED) + ")"
print(disp_str)

# CUDA should match only for ZED SDK < 3.6
if CUDA_INDEPENDANT_VERSION:
    if "aarch64" in ARCH_VERSION:
        if "jp" in CUDA_STR:
            CUDA_STR = CUDA_STR[:-1] # 'jp4', not 'jp45'
        whl_file_URL = base_URL + str(ZED_SDK_MAJOR) + "." + str(ZED_SDK_MINOR) + "/" + OS_VERSION + "/" + CUDA_STR + "/py" + str(PYTHON_MAJOR) + str(PYTHON_MINOR)
    else:
        whl_file_URL = base_URL + str(ZED_SDK_MAJOR) + "." + str(ZED_SDK_MINOR) + "/" + OS_VERSION + "/py" + str(PYTHON_MAJOR) + str(PYTHON_MINOR)
else:
    if (CUDA_MAJOR_ZED != CUDA_MAJOR or CUDA_MINOR_ZED != CUDA_MINOR) and OS_VERSION != "jetsons":
        print("ZED SDK requested a CUDA version that is different from the one detected on your system path")
        if sys.platform == "win32":
            print("Either the 'CUDA_PATH' environment variable is not pointing to the appropriate CUDA version or CUDA is not installed.")
        else:
            print("Either select a ZED SDK installer for " + str(CUDA_MAJOR) + "." + str(CUDA_MINOR) + " or install CUDA " + str(CUDA_MAJOR_ZED) + "." + str(CUDA_MINOR_ZED))
        sys.exit(1)
    whl_file_URL = base_URL + str(ZED_SDK_MAJOR) + "." + str(ZED_SDK_MINOR) + "/" + OS_VERSION + "/" + CUDA_STR + "/py" + str(PYTHON_MAJOR) + str(PYTHON_MINOR)


whl_file = "pyzed-" + str(ZED_SDK_MAJOR) + "." + str(ZED_SDK_MINOR) + whl_python_version + "-" + whl_platform_str + "_" + str(ARCH_VERSION).lower() + ".whl"
whl_file = os.path.join(dirname, whl_file)

print("-> Checking if " + whl_file_URL + " exists and is available")
urllib.request.urlretrieve(whl_file_URL, whl_file)
# Warning doesn't handle missing remote file yet and will probably download an html

if check_valid_file(whl_file):
    # Internet is ok, file has been downloaded and is valid
    print("-> Found ! Downloading python package into " + whl_file)

    print("-> Installing necessary dependencies")
    err = 0
    if "aarch64" in ARCH_VERSION:
        # On jetson numpy is built from source and need other packages
        err_wheel = pip_install("wheel")
        err_cython = pip_install("cython")
        err = err_wheel + err_cython
    err_numpy = pip_install("numpy")

    if err != 0 or err_numpy != 0:
        print("ERROR : An error occured, 'pip' failed to setup python dependencies packages (pyzed was NOT correctly setup)")
        sys.exit(1)

    err_pyzed = pip_install(whl_file, force_install=True)
    if err_pyzed == 0:
        print("Done")
    else:
        print("ERROR : An error occured, 'pip' failed to setup pyzed package (pyzed was NOT correctly setup)")
        sys.exit(1)

    if sys.platform == "win32" :
        print("Installing OpenGL dependencies required to run the samples")
        py_vers = int(int(PYTHON_MAJOR) *math.pow(10,len(PYTHON_MINOR)) + int(PYTHON_MINOR))
        install_win_dep("PyOpenGL", py_vers)
        install_win_dep("PyOpenGL_accelerate", py_vers)

        # Two files must be copied into pyzed folder : sl_zed64.dll and sl_ai64.dll
        pyzed_dir = get_pyzed_directory()
        source_dir = zed_path + "/bin"
        files = ["/sl_ai64.dll","/sl_zed64.dll"]

        for file in files:
            if os.path.isfile(source_dir + file):           
                shutil.copy(source_dir + file, pyzed_dir + file)
            else:
                print("ERROR : An error occured, 'pip' failed to copy dll file " + source_dir + file + " (pyzed was NOT correctly setup)")

    print("  To install it later or on a different environment run : \n python -m pip install --ignore-installed "+ whl_file)
    sys.exit(0)
else:
    print("\nUnsupported platforms, no pyzed file available for this configuration\n It can be manually installed from source https://github.com/stereolabs/zed-python-api")
    sys.exit(1)
