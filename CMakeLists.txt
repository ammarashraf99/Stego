cmake_minimum_required(VERSION 3.31.6)
project(stego LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(-ggdb)

include(FetchContent)

# Fetch cxxopts from GitHub
FetchContent_Declare(
  cxxopts
  GIT_REPOSITORY https://github.com/jarro2783/cxxopts.git
  GIT_TAG v3.2.0 # latest stable tag as of now
)

FetchContent_MakeAvailable(cxxopts)

include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(stegtool
  src/main.cpp
  src/stego.cpp
  src/image.cpp
  src/lsb_embedder.cpp
  )


find_package(OpenCV REQUIRED)

# Link against cxxopts
target_link_libraries(stegtool PRIVATE cxxopts ${OpenCV_LIBS})
