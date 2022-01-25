cmake_minimum_required(VERSION 3.20)
project(bloom_filter)

set(CMAKE_CXX_STANDARD 23)
enable_testing()
add_executable(test_c test_c.cpp ../refac.h ../refac.c)
target_link_libraries(test_c gtest gtest_main)