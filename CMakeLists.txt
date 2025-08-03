cmake_minimum_required(VERSION 3.10)
project(PRG3DAG)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Debug)

add_executable(main
    src/main.cpp
    src/bmp_processing.cpp
)

target_include_directories(main PRIVATE include/)