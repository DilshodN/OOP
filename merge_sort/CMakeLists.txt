cmake_minimum_required(VERSION 3.20)
project(merge_sort)

set(CMAKE_CXX_STANDARD 23)

add_executable(merge_sort main.cpp)
add_subdirectory(test)
