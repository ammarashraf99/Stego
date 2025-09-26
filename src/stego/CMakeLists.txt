add_library(stego stego.cpp)

target_include_directories(stego
  PUBLIC ${cmake_source_dir}/include/stego
  PUBLIC ${cmake_source_dir}/include/image
)

