cmake_minimum_required(VERSION 3.16)

add_library(rfui STATIC rfui.cpp basicClasses.cpp)
target_include_directories(rfui PUBLIC "${PROJECT_SOURCE_DIR}/include")
