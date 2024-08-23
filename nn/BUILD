load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
    name = "nn-lib",

    srcs = ["nn.cpp",
            "layer.cpp",
            "perceptron.cpp",
            "matrix.cpp"],

    hdrs =  ["nn.hpp",
             "layer.hpp",
             "perceptron.hpp",
             "matrix.hpp"],

    visibility = ["//main:__pkg__"],
    
    #"//visibility:public" # seen by everyone
    #"//test:__pkg__",  # private visibility only to tests
    #"//main:__pkg__"], # private visibility only to main
)

