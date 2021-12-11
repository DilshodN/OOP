#pragma once

#include "editor.h"
#include "parser.h"
#include "command_creator.h"

class EditorManager final {
    Editor& editor;
    CommandParser& parser;
public:
    EditorManager() = delete;
    explicit EditorManager(Editor& editor, CommandParser& parser);
    void execute() const;
};