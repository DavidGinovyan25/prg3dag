cmake_minimum_required(VERSION 3.10)
project(PRG3DAG)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${CMAKE_SOURCE_DIR}/include)

add_subdirectory(src)      
add_subdirectory(bin)      