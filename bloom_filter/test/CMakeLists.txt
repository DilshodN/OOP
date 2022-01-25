cmake_minimum_required(VERSION 3.20)
project(bloom_filter)

set(CMAKE_CXX_STANDARD 23)
enable_testing()
add_executable(test test.cpp ../bloom_filter.h ../refac.h ../refac.c)
target_link_libraries(test gtest gtest_main)