#include "delete.h"

DeleteCommand::DeleteCommand(TextDocument &text, const size_t &start, const size_t &end):
        EditorCommand(text), start(start), end(end){}

void DeleteCommand::execute() {
    erased = text.substr(start, end);
    text.erase(start, end);
}
void DeleteCommand::undo() {
    text.insert(erased, start);
}