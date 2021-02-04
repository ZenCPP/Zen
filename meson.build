
project('zen', 'cpp')

cmake = import('cmake')

gtest_proj = subproject('gtest')
gtest_dep = gtest_proj.get_variable('gtest_dep')
gtest_main_dep = gtest_proj.get_variable('gtest_main_dep')

zen_lib = static_library(
  'zen',
  'zen/cli.cc',
  include_directories: '.',
  override_options: ['cpp_std=c++17'],
)

zen_dep = declare_dependency(
  link_with: zen_lib,
  include_directories: '.',
)

alltests = executable(
  'alltests',
  include_directories: '.',
  dependencies: [ zen_dep, gtest_dep, gtest_main_dep ],
)
