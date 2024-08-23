load("@rules_cc//cc:defs.bzl", "cc_toolchain")
load(":m1_mac_arm64_cc_toolchain_config.bzl", "cc_toolchain_config")

cc_toolchain_config(
    name = "m1_mac_arm64_cc_toolchain_config"
)

cc_toolchain(
    name = "m1_mac_arm64_toolchain",
    toolchain_identifier = "m1_mac_arm64-toolchain",
    toolchain_config = ":m1_mac_arm64_cc_toolchain_config",
    all_files = ":empty",
    compiler_files = ":empty",
    dwp_files = ":empty",
    linker_files = ":empty",
    objcopy_files = ":empty",
    strip_files = ":empty",
    supports_param_files = 0,
)

toolchain(
    name = "cc_toolchain_for_m1_mac_arm64",
    toolchain = ":m1_mac_arm64_toolchain",
    toolchain_type = "@bazel_tools//tools/cpp:toolchain_type",

    exec_compatible_with = [
        "@platforms//cpu:arm64",
        "@platforms//os:macos",
    ],
    target_compatible_with = [
        "@platforms//cpu:arm64",
        "@platforms//os:macos",
    ],
)

filegroup(name = "empty")
package(default_visibility = ["//visibility:public"])
