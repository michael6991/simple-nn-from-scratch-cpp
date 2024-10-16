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
    visibility = ["//visibility:public"],
)

