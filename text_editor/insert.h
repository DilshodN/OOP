#pragma once
#include "editor_command.h"

class InsertCommand final : public EditorCommand{
    size_t start;
    std::string inserted;
public:
    InsertCommand(std::string str, const size_t start);
    void execute(TextDocument& text) override;
    void undo(TextDocument& text) override;
};