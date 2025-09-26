add_library(lsb_embedder lsb_embedder.cpp)

target_include_directories(lsb_embedder
  PUBLIC ${CMAKE_SOURCE_DIR}/include/lsb_embedder
  PUBLIC ${CMAKE_SOURCE_DIR}/include/embedder
)
