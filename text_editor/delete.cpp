#include "delete.h"

DeleteCommand::DeleteCommand(const size_t &start, const size_t &end):
        start(start), end(end){}

void DeleteCommand::execute(TextDocument &text) {
    erased = text.substr(start, end);
    text.erase(start, end);
}
void DeleteCommand::undo(TextDocument &text) {
    text.insert(erased, start);
}
