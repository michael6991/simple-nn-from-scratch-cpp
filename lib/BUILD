load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
    name = "nn",

    srcs = glob([
        "src/**/*.cpp",
        "src/**/*.c",
    ]),

    hdrs = glob([
        "include/**/*.hpp",
        "include/**/*.h"
    ]),

    includes = [
        "include",
        "../external/opencv/install/include/opencv4",
    ],
    deps =[
        "@opencv//:opencv"
    ],

    copts = [
        "-std=c++20",
        "-g",
        "-Iexternal/opencv/install/include/opencv4",
        "-Lexternal/opencv/install/lib",
        "-lopencv_core",
        "-lopencv_imgcodecs",
        "-lopencv_highgui",
    ],

    visibility = ["//visibility:public"],
)

