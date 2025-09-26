add_library(image image.cpp)

target_include_directories(image
  PUBLIC ${CMAKE_SOURCE_DIR}/include/image
)
