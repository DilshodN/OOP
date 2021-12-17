#pragma once
#include "editor_command.h"
class PasteCommand final : public EditorCommand{
    size_t start;
public:
    PasteCommand(const size_t start);
    void execute(TextDocument& text) override;
    void undo(TextDocument& text) override;
};