cmake_minimum_required(VERSION 3.31.6)
project(stego LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(-ggdb)


########################################################
include(FetchContent)

# Fetch cxxopts from GitHub
FetchContent_Declare(
  cxxopts
  GIT_REPOSITORY https://github.com/jarro2783/cxxopts.git
  GIT_TAG v3.2.0 # latest stable tag as of now
)

FetchContent_MakeAvailable(cxxopts)
find_package(OpenCV REQUIRED)
find_package(OpenSSL REQUIRED)
#######################################################



include_directories(${CMAKE_SOURCE_DIR}/include)

#####################
add_subdirectory(src)
#####################


target_link_libraries(crypto PRIVATE OpenSSL::SSL OpenSSL::Crypto)

target_link_libraries(image PUBLIC ${OpenCV_LIBS})
target_link_libraries(lsb_embedder
  PUBLIC image
  PRIVATE crypto)
target_link_libraries(stego
  PRIVATE lsb_embedder
  PUBLIC cxxopts)
target_link_libraries(stegtool PRIVATE stego)
