cmake_minimum_required(VERSION 3.16)

add_executable(dstui main.cpp)
target_include_directories(dstui PUBLIC "${PROJECT_SOURCE_DIR}/include")
target_link_libraries(dstui rfui)
