bat_srcs = [
  'bat.c',
]

inc = get_variable('inc', join_paths(meson.current_source_dir(),'..'))

bat_include_dirs = [
  '.',
   '../submodules/c_deps/submodules/reproc/reproc/include/reproc',
   '../submodules/c_deps/submodules/reproc/reproc/include',
  inc,
]

bat_deps = [
  ansi_codes_dep,
  c_vector_dep,
  c_fsio_dep,
  c_stringfn_dep,
  c_string_buffer_dep,
  timestamp_dep,
  log_dep,
  ms_dep,
  bytes_dep,
  reproc_dep,which_dep,tempdir_dep,
]

bat_c_args = [
]

bat_link_args = [
]

bat_lib = library('bat',
  bat_srcs,
  install: false,
  dependencies: bat_deps,
  c_args: bat_c_args,
  include_directories: bat_include_dirs
)

bat_dep = declare_dependency(
  include_directories: bat_include_dirs,
  link_with: bat_lib,
  link_args: bat_link_args,
)
