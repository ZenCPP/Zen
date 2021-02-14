
project('zen', 'cpp')

cmake = import('cmake')

gtest_proj = subproject('gtest')
gtest_dep = gtest_proj.get_variable('gtest_dep')
gtest_main_dep = gtest_proj.get_variable('gtest_main_dep')

zen_sources = [
  'zen/fs_common.cc',
]

zen_enable_intrinsics = get_option('intrinsics')

zen_namespace = get_option('namespace')
zen_namespace_start = ''
zen_namespace_end = ''

foreach name : zen_namespace.split('::')
  zen_namespace_start += 'namespace ' + name + ' {'
  zen_namespace_end += '}'
endforeach

zen_lexgen_sources = [
  'zen/lexgen/parser.cc',
  'zen/lexgen/lexer.cc',
  'zen/lexgen/minimize.cc',
]

if target_machine.system() == 'linux'
  zen_sources += [
    'zen/fs_posix.cc'
  ]
endif

zen_compile_args = [
  '-fno-rtti',
  '-fno-exceptions',
  '-Wall',
  '-DZEN_NAMESPACE=' + zen_namespace,
  '-DZEN_NAMESPACE_START=' + zen_namespace_start,
  '-DZEN_NAMESPACE_END=' + zen_namespace_end,
]

if get_option('nostdlib')
  zen_compile_args += [
    '-nostdlib',
  ]
else
  zen_compile_args += [
    '-DZEN_STL=1',
  ]
endif

cpp = meson.get_compiler('cpp')

if zen_enable_intrinsics

  if cpp.compiles(
'''
#include <utility>
using T = __make_integer_seq<std::integer_sequence, int, 10>;
''',
    name: '__make_integer_seq',
  )
    zen_compile_args += [
      '-DZEN_FEAT_MAKE_INTEGER_SEQ=1',
    ]
  endif

  if cpp.compiles(
'''
using T = __type_pack_element<1, short, int, long>;
''',
    name: '__type_pack_element',
  )
    zen_compile_args += [
      '-DZEN_FEAT_TYPE_PACK_ELEMENT=1',
    ]
  endif

endif

zen_lib = static_library(
  'zen',
  zen_sources,
  include_directories: '.',
  cpp_args: zen_compile_args,
  override_options: ['cpp_std=c++2a'],
)

zen_dep = declare_dependency(
  link_with: zen_lib,
  compile_args: zen_compile_args,
  include_directories: '.',
)

executable(
  'zen-lexgen',
  'zen/lexgen/main.cc',
  zen_lexgen_sources,
  link_with: zen_lib,
  include_directories: '.',
  override_options: ['cpp_std=c++2a'],
)

executable(
  'po-example',
  'zen/po_sample_main.cc',
  link_with: zen_lib,
  override_options: ['cpp_std=c++2a'],
  build_by_default: false,
)

executable(
  'alltests',
  'zen/meta_test.cc',
  'zen/common_test.cc',
  'zen/serde_test.cc',
  'zen/dllist_test.cc',
  'zen/either_test.cc',
  'zen/vector_test.cc',
  'zen/clone_ptr_test.cc',
  'zen/fs_test.cc',
  'zen/po_test.cc',
  'zen/lexgen/lexer_test.cc',
  'zen/lexgen/parser_test.cc',
  zen_lexgen_sources,
  include_directories: '.',
  cpp_args: [ '-Wall' ],
  dependencies: [ zen_dep, gtest_dep, gtest_main_dep ],
  override_options: ['cpp_std=c++2a'],
  build_by_default: false,
)

