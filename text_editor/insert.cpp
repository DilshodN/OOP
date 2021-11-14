#include "insert.h"

InsertCommand::InsertCommand(TextDocument& text, std::string&& str, const size_t &start):
        EditorCommand(text), inserted(str), start(start){}

void InsertCommand::execute() {
    text.insert(inserted, start);
}
void InsertCommand::undo() {
    size_t previous_start = start >= text.size() ? start = text.size() - inserted.size() : start;
    text.erase(previous_start, previous_start + inserted.size());
}