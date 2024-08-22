load("@bazel_tools//tools/build_defs/cc:action_names.bzl", "ACTION_NAMES")

load("@bazel_tools//tools/cpp:cc_toolchain_config_lib.bzl",
    "feature", 
    "flag_group",
    "flag_set",
    "tool_path")


def _impl(ctx):
    tool_paths = [
        tool_path(
            name = "gcc",
            path = "/usr/bin/clang",
        ),
        tool_path(
            name = "ld",
            path = "/usr/bin/ld",
        ),
        tool_path(
            name = "ar",
            path = "/usr/bin/ar",
        ),
        tool_path(
            name = "cpp",
            path = "/usr/bin/clang++",
        ),
        tool_path(
            name = "gcov",
            path = "/usr/bin/gcov",
        ),
        tool_path(
            name = "nm",
            path = "/usr/bin/nm",
        ),
        tool_path(
            name = "objdump",
            path = "/usr/bin/objdump",
        ),
        tool_path(
            name = "strip",
            path = "/usr/bin/strip",
        ),
    ]

    features = [
        feature(
            name = "default_compiler_flags",
            enabled = True,
            flag_sets = [
                flag_set(
                    actions = [
                        ACTION_NAMES.c_compile,
                        ACTION_NAMES.cpp_compile,
                    ],
                    flag_groups = ([
                        flag_group(
                            flags = [
                                "-Wall",
                                "-fPIC",
                                # "-march=armv8-a",
                            ],
                        ),
                    ]),
                ),
            ],
        ),
    ]

    return cc_common.create_cc_toolchain_config_info(
        ctx = ctx,
        features = features,
        cxx_builtin_include_directories = [
            "/Library/Developer/CommandLineTools/usr/include/c++/v1",
            "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include",
            "/Library/Developer/CommandLineTools/usr/lib/clang/15.0.0/include",
            "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/System/Library/Frameworks",
        ],
        toolchain_identifier = "local",
        host_system_name = "local",
        target_system_name = "local",
        target_cpu = "darwin_arm64",
        target_libc = "macosx",
        compiler = "clang",
        abi_version = "darwin_arm64",
        abi_libc_version = "darwin_arm64",
        tool_paths = tool_paths,
    )

cc_toolchain_config = rule(
    implementation = _impl,
    attrs = {},
    provides = [CcToolchainConfigInfo],
)

