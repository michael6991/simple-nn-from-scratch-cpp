# Simple NN from Scratch C++20

To compile:
clang++ -std=c++20 -o myprogram main.cpp

clang++ -std=c++20 -o out/test_matrix test_matrix.cpp matrix.cpp

bazel build //main:program

use: --subcommands in bazel build to see more info (-s)
use: bazel clean --expunge to clean bazel build products


## how to install and add opencv to project
https://stackoverflow.com/questions/34984290/how-to-use-bazel-to-build-project-uses-opencv

<!-- simple example compilation with opencv  -->
clang++ a.cpp -o a.out -std=c++20 -I/opt/homebrew/opt/opencv/include/opencv4 -L/opt/homebrew/opt/opencv/lib -lopencv_core -lopencv_imgcodecs -lopencv_highgui
