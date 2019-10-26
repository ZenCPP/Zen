
cmake_minimum_required(VERSION 3.0)

project(ZenCPP CXX)

set(CMAKE_CXX_STANDARD 14)

option(ZEN_ENABLE_TESTS OFF "Whether to generate the test infrastructure")

# This must be added before doing any other configuration so that
# changing something local doesn't trigger a GoogleTest rebuild
if (ZEN_ENABLE_TESTS)
  add_subdirectory(third_party/googletest)
endif()

include_directories(include/)

if (ZEN_ENABLE_TESTS)

  file(GLOB_RECURSE test_files test/*.cpp)
  add_executable(runTests ${test_files})
  target_link_libraries(runTests gtest gtest_main)

  # At the time of writing a bug in CMake still exists that causes the tests
  # not to be built when invoking 'make test'. Therefore, we create a custom
  # target.
  add_custom_target(check COMMAND runTests DEPENDS runTests)

endif()

