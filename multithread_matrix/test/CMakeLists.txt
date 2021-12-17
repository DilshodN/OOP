cmake_minimum_required(VERSION 3.20)
project(multithread_matrix)

set(CMAKE_CXX_STANDARD 20)

add_executable(test test.cpp ../matrix.h ../matrix.cpp ../calculator_manager.cpp ../calculator_manager.h)
target_link_libraries(test gtest gtest_main)