#pragma once
#include "editor_command.h"

class DeleteCommand final : public EditorCommand{
    size_t start, end;
    std::string erased;
public:
    DeleteCommand(const size_t& start, const size_t& end);
    void execute(TextDocument& text) override;
    void undo(TextDocument& text) override;
};