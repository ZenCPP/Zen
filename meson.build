
project('zen', 'cpp')

cmake = import('cmake')

gtest_proj = subproject('gtest')
gtest_dep = gtest_proj.get_variable('gtest_dep')
gtest_main_dep = gtest_proj.get_variable('gtest_main_dep')

zen_sources = []

if target_machine.system() == 'linux'
  zen_sources += [
    'zen/fs_posix.cc'
  ]
endif

zen_lib = static_library(
  'zen',
  zen_sources,
  include_directories: '.',
  override_options: ['cpp_std=c++17'],
)

zen_dep = declare_dependency(
  link_with: zen_lib,
  include_directories: '.',
)

alltests = executable(
  'alltests',
  'zen/meta_test.cc',
  'zen/fs_test.cc',
  include_directories: '.',
  cpp_args: [ '-Wall' ],
  dependencies: [ zen_dep, gtest_dep, gtest_main_dep ],
  override_options: ['cpp_std=c++17'],
)

