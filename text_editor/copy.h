#pragma once
#include "editor_command.h"

class CopyCommand final : public EditorCommand{
    size_t start, end;
    std::string previous_text;
public:
    CopyCommand(const size_t& start, const size_t& end);
    void execute(TextDocument& text) override;
    void undo(TextDocument& text) override;
};