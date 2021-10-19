cmake_minimum_required(VERSION 3.20)
project(sum_all)

set(CMAKE_CXX_STANDARD 23)

enable_testing()
add_executable(test test.cpp test.cpp)
target_link_libraries(test gtest gtest_main)
