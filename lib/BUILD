load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
    name = "libnn",

    # Instead of writing manually all the names:
    srcs = glob(["src/*.cpp"]),
    hdrs = glob(["include/*.hpp"]),
    includes = ["include"],
    deps = [
        "@opencv//:opencv_core",
        "@opencv//:opencv_imgcodecs",
        "@opencv//:opencv_highgui",
    ],

    # copts = [
    #         "-I/opt/homebrew/opt/opencv/include/opencv4",
    #         "-L/opt/homebrew/opt/opencv/lib",
    #         "-lopencv_core",
    #         "-lopencv_imgcodecs",
    #         "-lopencv_highgui"],

    visibility = ["//visibility:public"],
    # "//test:__pkg__",  # private visibility only to tests
    # "//main:__pkg__"], # private visibility only to main
)

