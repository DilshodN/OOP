#include "paste.h"


PasteCommand::PasteCommand(TextDocument& text, std::string &buffer, const size_t &start):
        EditorCommand(text), pasted_text(buffer), start(start){}

void PasteCommand::execute() {
    text.insert(pasted_text, start);
}

void PasteCommand::undo() {
    text.erase(start, start + pasted_text.size());
}