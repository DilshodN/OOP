cmake_minimum_required(VERSION 3.20)
project(text_editor)

set(CMAKE_CXX_STANDARD 23)


add_executable(text_editor main.cpp text_document.h editor_command.h
        text_document.cpp editor.h parser.cpp parser.h editor.cpp copy.cpp copy.h insert.cpp insert.h paste.cpp paste.h delete.cpp delete.h commands_enum.h command_dto.cpp command_dto.h command_creator.cpp command_creator.h undo.cpp undo.h redo.cpp redo.h service_command.h editor_manager.cpp editor_manager.h buffer.h buffer.cpp)
add_subdirectory(test)