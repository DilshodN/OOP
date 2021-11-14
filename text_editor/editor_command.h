#pragma once
#include "text_document.h"

class EditorCommand{
protected:
    TextDocument& text;
public:
    EditorCommand() = delete;
    explicit EditorCommand(TextDocument& text) : text(text){};
    virtual void execute() = 0;
    virtual void undo() = 0;
    // redo is implemented in Editor class
    virtual ~EditorCommand() = default;
};