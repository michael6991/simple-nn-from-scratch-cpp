load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library")


# try this:
# copts = ["-Ilibs/foo/include"], # This is the key part
    # visibility = ["//visibility:public"],


cc_library(
    name = "net",
    srcs = ["nn.cpp"],
    hdrs = ["nn.hpp"],
    deps = [":layer"],
    visibility = ["//visibility:public"]
)

cc_library(
    name = "layer",
    srcs = ["layer.cpp"],
    hdrs = ["layer.hpp"],
    deps = [":mlp"],
)

cc_library(
    name = "mlp",
    srcs = ["perceptron.cpp"],
    hdrs = ["perceptron.hpp"],
    deps = [":matrix"],
)

cc_library(
    name = "matrix",
    srcs = ["matrix.cpp"],
    hdrs = ["matrix.hpp"],
)

cc_binary(
    name = "run-main",
    srcs = ["main.cpp"],
    deps = [
        ":net"
    ],
)


