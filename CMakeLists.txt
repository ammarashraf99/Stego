cmake_minimum_required(VERSION 3.31.6)
project(stego LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(-ggdb)


include_directories(${CMAKE_SOURCE_DIR}/include)


add_subdirectory(src)

target_link_libraries(image PUBLIC ${OpenCV_LIBS})
target_link_libraries(lsb_embedder PUBLIC image)
target_link_libraries(stego PUBLIC cxxopts PRIVATE lsb_embedder)

target_link_libraries(stegtool PRIVATE stego)

# Link against cxxopts
target_link_libraries(stegtool PRIVATE ${OpenCV_LIBS})
