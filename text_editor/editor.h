#pragma once
#include "text_document.h"
#include "command_dto.h"
#include <vector>

class Editor final{
    std::vector<std::unique_ptr<EditorCommand>> commands, undo_commands;
    TextDocument& text; // association!
    std::string buffer;
public:
    Editor() = delete;
    void execute(std::unique_ptr<EditorCommand> cmd);
    explicit Editor(TextDocument& text);
    void Undo();
    void Redo();
    void Save(std::ostream &out) const;
};