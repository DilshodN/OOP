cmake_minimum_required(VERSION 3.20)
project(bloom_filter)

set(CMAKE_CXX_STANDARD 20)

add_executable(bloom_filter main.cpp bloom_filter.h test_c/test_c.cpp)
add_subdirectory(test)
add_subdirectory(test_c)
