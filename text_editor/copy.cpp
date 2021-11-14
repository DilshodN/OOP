//
// Created by dilshod on 14.11.2021.
//

#include "copy.h"

CopyCommand::CopyCommand(TextDocument &text, std::string& buffer, const size_t &start, const size_t &end):
        EditorCommand(text), copied_text(buffer), start(start), end(end){}

void CopyCommand::execute() {
    previous_text = copied_text;
    copied_text = text.substr(start, end);
}

void CopyCommand::undo() {
    copied_text = previous_text;
}