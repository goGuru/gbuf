cmake_minimum_required (VERSION 2.8)
project (gbuf)

include_directories(inc)
file(GLOB SRCS src/*.cpp)

add_library(gbuf STATIC ${SRCS})

install(TARGETS gbuf DESTINATION ${CMAKE_BINARY_DIR}/../lib)