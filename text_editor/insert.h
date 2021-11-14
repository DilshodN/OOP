#pragma once
#include "editor_command.h"

class InsertCommand final : public EditorCommand{
    size_t start;
    const std::string inserted;
public:
    InsertCommand(TextDocument& text, std::string&& str, const size_t& start);
    void execute() override;
    void undo() override;
};