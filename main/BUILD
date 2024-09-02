load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library")

cc_binary(
    name = "main-prog",
    srcs = ["main.cpp"],
    deps = [
        "//lib:libnn",
    ],
    
     # Compiler options and try to include opencv lib
    # copts = ["-g",
            # "-std=c++17",
    # ],
            # "-I/opt/homebrew/opt/opencv/include/opencv4",
            # "-L/opt/homebrew/opt/opencv/lib",
            # "-lopencv_core",
            # "-lopencv_imgcodecs",
            # "-lopencv_highgui"],
)


