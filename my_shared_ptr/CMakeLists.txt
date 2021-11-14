cmake_minimum_required(VERSION 3.20)
project(my_shared_ptr)

set(CMAKE_CXX_STANDARD 17)

add_executable(my_shared_ptr main.cpp shared_ptr.h)
add_subdirectory(test)