cmake_minimum_required(VERSION 3.20)
project(SkipList)

set(CMAKE_CXX_STANDARD 23)

add_executable(SkipList main.cpp skiplist.h skipnode.h)
