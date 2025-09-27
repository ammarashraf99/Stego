add_library(stego stego.cpp)

target_include_directories(stego
  PUBLIC ${CMAKE_SOURCE_DIR}/include/lsb_embedder
  PUBLIC ${CMAKE_SOURCE_DIR}/include/stego
)
