# Mesa Imaging SwissRanger SR4000 (SR4K)

> This program currently only works with ethernet cameras

This repository hold an example program to interface with the SwissRanger ToF Camera. I also added the drivers needed to connect to the camera since they are hard to get because Mesa Imaging no longer exists. This code is based on  [austinoboyle/swissranger-driver](https://github.com/austinoboyle/swissranger-driver) and  [gurbain/ORF_standalone](https://github.com/gurbain/ORF_standalone).

## The data

This program will open a connection to the camera and show you the following images:

- Amplitude image (greyscale)
- Depth image
- Confidence image

The amplitude image is just a greyscale image of what the camera sees.

The Depth image shows you the depth that the camera sees. White means far away. Black is close to the camera.

The confidence map shows how confident the camera is about its measurement at every pixel. White means very confident, black means not.

## Installation/build

This program only runs on linux. I tested it on Ubuntu 18.04 in WSL2.

### Step 1 
First clone the repository and cd into it:

```bash
git clone https://github.com/egidiusmengelberg/mesa4k.git
cd mesa4k
```

### Step 2: 

Install the required tools and libraries:
- g++
- cmake
- OpenCV
- LibMesaSr

To install these run the following commands

```bash
# install g++
sudo apt-get install build-essential gdb
# install cmake
sudo apt-get install cmake
# install OpenCV
sudo apt-get install libopencv-dev
# install LibMesaSr
sudo install_driver.sh
```

### Step 3

Build the code

```bash
# create build directory
mkdir build
# cd into build directory
cd build
# run cmake
cmake ..
# run make and build the code
make
```

### Step 4

Run the program

please specify the ip address of the camera as an argument

```bash
./Mesa4K 192.168.1.2
```

## Questions

Please create an issue if something does not work or you need help.