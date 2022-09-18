cmake_minimum_required(VERSION 3.16)

add_library(rfui STATIC
        rfui.cpp
        basicClasses.h
        basicClasses/Label.cpp basicClasses/Label.h
        basicClasses/Root.cpp basicClasses/Root.h
        basicClasses/Widget.cpp basicClasses/Widget.h
        basicClasses/Input.cpp basicClasses/Input.h
        basicClasses/TextField.cpp basicClasses/TextField.h
        extern/format.cc
        extern/os.cc
        )
target_include_directories(rfui PUBLIC "${PROJECT_SOURCE_DIR}/include")
