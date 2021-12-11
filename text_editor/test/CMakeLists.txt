cmake_minimum_required(VERSION 3.20)
project(text_editor)

set(CMAKE_CXX_STANDARD 23)

add_executable(test ../text_document.cpp ../parser.cpp ../editor.cpp ../copy.cpp ../insert.cpp ../paste.cpp ../delete.cpp ../command_dto.cpp test.cpp ../command_creator.cpp ../command_creator.h ../undo.cpp ../undo.h ../redo.cpp ../redo.h ../service_command.h ../editor_command.h ../editor_manager.cpp ../buffer.h ../buffer.cpp)
target_link_libraries(test gtest gtest_main)