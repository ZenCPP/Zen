
cc_library(
  name = "lib",
  hdrs = ["include/zen/either.hpp", "include/zen/config.hpp"],
  includes = ["include"],
)

cc_test(
  name = "tests",
  srcs = glob(["test/*.cc"]),
  deps = [":lib", "@googletest//:gtest_main"],
)

cc_test(
  name = "tests_noexcept",
  srcs = glob(["test/*.cc"]),
  deps = [":lib", "@googletest//:gtest_main"],
  copts = ["-fno-exceptions"]
)

cc_test(
  name = "tests_nortti",
  srcs = glob(["test/*.cc"]),
  deps = [":lib", "@googletest//:gtest_main"],
  copts = ["-fno-rtti"]
)

