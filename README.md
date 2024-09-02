# deep-net-cpu

To compile:
clang++ -std=c++20 -o myprogram main.cpp

clang++ -std=c++20 -o out/test_matrix test_matrix.cpp matrix.cpp

bazel build //main:run

use: --subcommands in bazel build to see more info
use: bazel clean --expunge to clean bazel build products
