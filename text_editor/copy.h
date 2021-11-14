#pragma once
#include "editor_command.h"

class CopyCommand final : public EditorCommand{
    size_t start, end;
    std::string& copied_text;
    std::string previous_text;
public:
    CopyCommand(TextDocument& text, std::string& buffer, const size_t& start, const size_t& end);
    void execute() override;
    void undo() override;
};