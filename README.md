# deep-net-cpu

To compile:
clang++ -std=c++17 -o myprogram main.cpp

clang++ -std=c++17 -o out/test_matrix test_matrix.cpp matrix.cpp

bazel build --cpu=darwin_arm64 --apple_platform_type=macos //main-nn-run:main
