add_executable(stegtool main.cpp)

target_include_directories(stegtool
  PUBLIC ${CMAKE_SOURCE_DIR}/include/stego
  # PUBLIC ${CMAKE_SOURCE_DIR}/include/image
  # PUBLIC ${CMAKE_SOURCE_DIR}/include/embedder
  # PUBLIC ${CMAKE_SOURCE_DIR}/include/lsb_embedder
  # PUBLIC ${CMAKE_SOURCE_DIR}/include/crypto
)
