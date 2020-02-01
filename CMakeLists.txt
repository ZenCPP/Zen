
cmake_minimum_required(VERSION 3.0)

project(Zen CXX)

set(CMAKE_CXX_STANDARD 17)

option(ZEN_ENABLE_TESTS OFF "Whether to generate the test infrastructure")
option(ZEN_ENABLE_ASSERTIONS OFF "Force the compiler to generate assertions for certain invariants")

# This must be added before doing any other configuration so that
# changing something local doesn't trigger a GoogleTest rebuild
if (ZEN_ENABLE_TESTS)
  add_subdirectory(third_party/googletest EXCLUDE_FROM_ALL)
endif()

include_directories(include/)

add_custom_command(
  OUTPUT "${CMAKE_SOURCE_DIR}/include/zen/macros.h"
  COMMAND templaty --out-file "${CMAKE_SOURCE_DIR}/include/zen/macros.h" "${CMAKE_SOURCE_DIR}/include/zen/macros.h.tply"
  DEPENDS "${CMAKE_SOURCE_DIR}/include/zen/macros.h.tply"
  COMMENT "Generating zen/macros.h"
)

add_custom_target(
  docs
  DEPENDS "${CMAKE_SOURCE_DIR}/include/zen/macros.h"
  COMMAND doxygen
  WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
  COMMENT "Generating documentation"
)

add_library(zen_base INTERFACE)
target_include_directories(zen_base INTERFACE include/)
set_target_properties(zen_base PROPERTIES PUBLIC_HEADER "include/zen/macros.h;include/zen/meta.hpp;include/zen/either.hpp;include/zen/value.hpp")
add_dependencies(zen_base "${CMAKE_SOURCE_DIR}/include/zen/macros.h")

add_library(zen_cli src/zen_cli.cc)
set_target_properties(zen_cli PROPERTIES PUBLIC_HEADER "include/zen/cli.hpp")
target_link_libraries(zen_cli zen_base)

add_library(zen_full INTERFACE)
add_dependencies(zen_full zen_base zen_cli)

install(TARGETS zen_base zen_cli PUBLIC_HEADER DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/zen")

if (ZEN_ENABLE_TESTS)

  set(ZEN_TEST_TARGETS "")

  macro(add_gtest name)
    add_executable("${name}" ${ARGN})
    target_link_libraries("${name}" gtest gtest_main zen_full)
    add_custom_target("test_${name}" COMMAND "${name}" --gtest_color=yes COMMENT "Running tests ${name}")
    list(APPEND ZEN_TEST_TARGETS "test_${name}")
  endmacro()

  add_gtest(zen_macros test/test_zen_macros.cc)

  # We create our own test target that does nothing more than runnning all
  # GoogleTest executables and printing the results. We could use CMake's
  # built-in testing infrastructure, but it seems like this technique is more
  # than enough.
  add_custom_target(test DEPENDS ${ZEN_TEST_TARGETS})

endif()


