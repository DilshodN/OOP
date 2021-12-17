cmake_minimum_required(VERSION 3.20)
project(blur_image)

set(CMAKE_CXX_STANDARD 20)

add_executable(blur_image main.cpp app.cpp app.h blur_info.cpp blur_info.h blur_image.cpp blur_image.h gui.cpp gui.h)
