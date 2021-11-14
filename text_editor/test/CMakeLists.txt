cmake_minimum_required(VERSION 3.20)
project(text_editor)

set(CMAKE_CXX_STANDARD 23)

add_executable(test ../text_document.cpp ../parser.cpp ../editor.cpp ../copy.cpp ../insert.cpp ../paste.cpp ../delete.cpp test.cpp)
target_link_libraries(test gtest gtest_main)