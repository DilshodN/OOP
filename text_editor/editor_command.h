#pragma once
#include "text_document.h"

class EditorCommand{
public:
    virtual void execute(TextDocument& text) = 0;
    virtual void undo(TextDocument& text) = 0;
    virtual ~EditorCommand() = default;
};