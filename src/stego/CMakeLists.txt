include(FetchContent)

# Fetch cxxopts from GitHub
FetchContent_Declare(
  cxxopts
  GIT_REPOSITORY https://github.com/jarro2783/cxxopts.git
  GIT_TAG v3.2.0 # latest stable tag as of now
)

FetchContent_MakeAvailable(cxxopts)
find_package(OpenCV REQUIRED)


add_library(stego stego.cpp)

target_include_directories(stego
  PUBLIC ${cmake_source_dir}/include/stego
  PUBLIC ${cmake_source_dir}/include/image
)

