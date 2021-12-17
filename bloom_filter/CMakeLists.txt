cmake_minimum_required(VERSION 3.20)
project(bloom_filter)

set(CMAKE_CXX_STANDARD 20)

add_executable(bloom_filter main.cpp base_filter.h null_filter.h bloom_filter.h)
add_subdirectory(test)
