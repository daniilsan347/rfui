cmake_minimum_required(VERSION 3.16)
project(dstui)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0")

set(CMAKE_CXX_STANDARD 20)
add_subdirectory(app)
add_subdirectory(src)

