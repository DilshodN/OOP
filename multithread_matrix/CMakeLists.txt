cmake_minimum_required(VERSION 3.20)
project(multithread_matrix)

set(CMAKE_CXX_STANDARD 20)

add_executable(multithread_matrix main.cpp matrix.h matrix.cpp calculator_manager.cpp calculator_manager.h)
add_subdirectory(test)