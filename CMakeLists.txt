
cmake_minimum_required(VERSION 3.0)

project(Zen CXX)

set(CMAKE_CXX_STANDARD 17)

if ("${CMAKE_BUILD_TYPE}" STREQUAL "Debug" OR "${CMAKE_BUILD_TYPE}" STREQUAL "RelWithDebInfo")
  set(ZEN_IS_DEBUG_BUILD ON)
else()
  set(ZEN_IS_DEBUG_BUILD OFF)
endif()

option(ZEN_ENABLE_TESTS "Whether to generate the test infrastructure" "${ZEN_IS_DEBUG_BUILD}")
option(ZEN_ENABLE_ASSERTIONS "Force the compiler to generate assertions for certain invariants" "${ZEN_IS_DEBUG_BUILD}")

if (ZEN_ENABLE_ASSERTIONS)
  message("-- Compiling Zen++ with assertions enabled")
endif()

# This must be added before doing any other configuration so that
# changing something local doesn't trigger a GoogleTest rebuild
if (ZEN_ENABLE_TESTS)
  add_subdirectory(third_party/googletest EXCLUDE_FROM_ALL)
endif()

add_library(
  zen
  zen/cli.cc
)
target_include_directories(zen INTERFACE "${CMAKE_SOURCE_DIRECTORY}")
target_compile_features(zen INTERFACE cxx_std_17)

install(
  DIRECTORY "${CMAKE_SOURCE_DIRECTORY}/zen"
  DESTINATION include/zen
  FILES_MATCHING PATTERN "*.h" PATTERN "*.hpp"
)
install(TARGETS zen EXPORT Zen)
install(EXPORT Zen DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake")

if (ZEN_ENABLE_TESTS)
  add_executable(testall zen/macros_test.cc zen/clone_ptr_test.cc zen/cli_test.cc)
  target_link_libraries(testall zen gtest gtest_main)
  add_custom_target(check COMMAND testall --gtest_color=yes COMMENT "Running tests")
endif()

