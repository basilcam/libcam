cmake_minimum_required(VERSION 3.15)
project(libcam C)

set(CMAKE_C_STANDARD 99)

add_library(cam STATIC
        src/sys/process.c
        src/sys/io.c
        src/error.c
        src/data/linked_list.c
        src/sys/signal.c
        src/sio.c
        src/algo/sort.c
        src/data/hashtable.c src/data/heap.c include/cam/data/heap.h)
target_include_directories(cam PUBLIC include)

add_subdirectory(examples)

