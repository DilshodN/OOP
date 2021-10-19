cmake_minimum_required(VERSION 3.20)
project(merge_sort)
enable_testing()
set(CMAKE_CXX_STANDARD 23)

add_executable(test test.cpp)
target_link_libraries(test gtest gtest_main)