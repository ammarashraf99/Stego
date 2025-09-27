add_library(crypto crypto.cpp)

target_include_directories(crypto
  PUBLIC ${CMAKE_SOURCE_DIR}/include/crypto
)
