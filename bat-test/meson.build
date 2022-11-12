bat_test_srcs = [
  'bat-test.c',
]
inc = get_variable('inc', join_paths(meson.current_source_dir(),'..'))
bat_test_include_dirs = [
  '.',
  inc,
]
bat_test_deps = [
  c_greatest_dep,
  ansi_codes_dep,
  c_vector_dep,
  c_fsio_dep,
  c_stringfn_dep,
  c_string_buffer_dep,
  timestamp_dep,
  log_dep,
  ms_dep,
  bytes_dep,
  bat_dep,
]
bat_test_c_args = [
]
bat_test_link_args = [
]

bat_test_test_dir = join_paths(meson.current_source_dir(), '..')

if get_option('enable-binaries')
  bat_test_exec = executable('bat-test',
     bat_test_srcs,
     dependencies: bat_test_deps,
     include_directories: bat_test_include_dirs,
     link_args: bat_test_link_args,
     c_args: bat_test_c_args,
     install: false,
  )
  test('bat-test', 
    bat_test_exec, args: ['-v','-a'],
    workdir: bat_test_test_dir,
  )
endif
