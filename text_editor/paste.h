#pragma once
#include "editor_command.h"

class PasteCommand final : public EditorCommand{
    size_t start;
    std::string& pasted_text;
public:
    PasteCommand(TextDocument& text, std::string& buffer, const size_t& start);
    void execute() override;
    void undo() override;
};