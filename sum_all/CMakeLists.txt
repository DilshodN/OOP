cmake_minimum_required(VERSION 3.20)
project(sum_all)

set(CMAKE_CXX_STANDARD 23)

add_executable(sum_all main.cpp sum_all.h sum_all_traits.h)
add_subdirectory(tests)
