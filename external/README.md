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

opencv.BUILD file should be located under: /path/to/opencv/install/
and will contain:

cc_library(
    name = "opencv",
    # srcs = glob(["lib/*.so*"]), # link shared object for linux
    srcs = glob(["lib/*.dylib"]), # link dynamic libraries for m1 mac
    
    hdrs = glob([
        "include/opencv4/**/*.hpp",
        "include/opencv4/**/*.h",
    ]),
    
    includes = ["include/opencv4"],
    visibility = ["//visibility:public"], 

    # linkstatic = 1,
    # linkshared = 1,
)

