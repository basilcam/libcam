cmake_minimum_required(VERSION 3.15)
project(libcam C)

set(CMAKE_C_STANDARD 99)

add_library(cam STATIC 
    src/sys/process.c
    src/sys/io.c
    src/error.c)
target_include_directories(cam PUBLIC include)

#add_subdirectory(examples)

