# External Use of Necessary Public Libraries
I download and build opencv locally, then use its object files to build with my custom neural network library in Bazel.

## To build opencv locally:
git clone https://github.com/opencv/opencv.git
cd opencv
mkdir build install
cd build
## for M1 Mac:
cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_SYSTEM_PROCESSOR=arm64 -DCMAKE_OSX_ARCHITECTURES=arm64 -DCMAKE_INSTALL_PREFIX=/path/to/opencv/install ..
make install

