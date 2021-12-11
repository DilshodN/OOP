#include "insert.h"

InsertCommand::InsertCommand(std::string& str, const size_t &start):
            inserted(str), start(start){}

void InsertCommand::execute(TextDocument& text) {
    text.insert(inserted, start);
}
void InsertCommand::undo(TextDocument& text) {
    size_t previous_start = start >= text.size() ? start = text.size() - inserted.size() : start;
    text.erase(previous_start, previous_start + inserted.size());
}
