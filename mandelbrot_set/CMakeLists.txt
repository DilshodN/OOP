cmake_minimum_required(VERSION 3.20)
project(mandelbrot_set)

set(CMAKE_CXX_STANDARD 11)

add_executable(mandelbrot_set main.cpp)
find_package(SFML REQUIRED graphics)
target_link_libraries(mandelbrot_set sfml-graphics)
