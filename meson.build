project('colon', 'cpp',
  default_options : ['cpp_std=c++20', 'warning_level=2']
)

cpp = meson.get_compiler('cpp')

# Common compile args
common_cflags = ['-Wall', '-Wextra', '-pedantic']

inc = include_directories('include')

# Source files
source_files = ['src/lexer.cpp', 'src/token.cpp']
main_file = ['src/main.cpp']
test_files = ['tests/lexer_test.cpp', 'tests/simple_test.cpp']

executable('colon', source_files + main_file,
  include_directories: inc,
  cpp_args: common_cflags,
  install: true
)

test_exe = executable('test_exe', source_files + test_files,
  include_directories: inc,
  cpp_args: common_cflags,
)

test('run_tests', test_exe)

