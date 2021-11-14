#pragma once
#include "editor_command.h"

class DeleteCommand final : public EditorCommand{
    size_t start, end;
    std::string erased;
public:
    DeleteCommand(TextDocument& text, const size_t& start, const size_t& end);
    void execute() override;
    void undo() override;
};