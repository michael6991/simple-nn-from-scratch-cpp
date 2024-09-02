load("@bazel_tools//tools/build_defs/cc:action_names.bzl", "ACTION_NAMES")

load("@bazel_tools//tools/cpp:cc_toolchain_config_lib.bzl",
    "feature", 
    "flag_group",
    "flag_set",
    "tool_path")

all_link_actions = [
    ACTION_NAMES.cpp_link_static_library,
    ACTION_NAMES.cpp_link_executable,
    ACTION_NAMES.cpp_link_dynamic_library,
    ACTION_NAMES.cpp_link_nodeps_dynamic_library,
]

def _impl(ctx):
    print("Using M1 ARM 64-bit MacOS Clang Toolchain")

    tool_paths = [
        tool_path(
            name = "gcc",
            path = "/usr/bin/clang",
        ),
        tool_path(
            name = "cpp",
            path = "/usr/bin/clang++",
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
                                "-std=c++20", # use new c++20 standard
                                "-Wall",      # show all warnings
                                "-g",         # generate debug symbols
                                # "-fPIC",
                                # "-march=armv8-a",
                            ],
                        ),
                    ]),
                ),
            ],
        ),

        feature(
            name = "default_linker_flags",
            enabled = True,
            flag_sets = [
                flag_set(
                    actions = all_link_actions,
                    flag_groups = ([
                        flag_group(
                            flags = [
                                "-lstdc++",
                                "-lopencv_core",
                                "-lopencv_imgcodecs",
                                "-lopencv_highgui",
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
        tool_paths = tool_paths,

        toolchain_identifier = "m1_arm64-toolchain",
        host_system_name = "local",
        target_system_name = "local",

        target_cpu = "darwin_arm64",
        target_libc = "macosx",

        # compiler = "clang++",
        compiler = "cpp",

        abi_version = "darwin_arm64",
        abi_libc_version = "darwin_arm64",

        cxx_builtin_include_directories = [
            "/Library/Developer/CommandLineTools/usr/lib/clang/16/include",
            "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include",
            "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/System/Library/Frameworks",
            # opencv lib
            "/opt/homebrew/opt/opencv/include/opencv4",
            "/opt/homebrew/opt/opencv/lib",
        ],
    )

cc_toolchain_config = rule(
    implementation = _impl,
    attrs = {},
    provides = [CcToolchainConfigInfo],
)
