
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

