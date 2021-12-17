#include "insert.h"

InsertCommand::InsertCommand(std::string str, const size_t start):
            inserted(std::move(str)), start(start){}

void InsertCommand::execute(TextDocument& text) {
    text.insert(inserted, start);
}
void InsertCommand::undo(TextDocument& text) {
    size_t previous_start = 0;
    if(start >= text.size()){
        start = text.size() - inserted.size();
    }
    else{
        previous_start = start;
    }
    text.erase(previous_start, previous_start + inserted.size());
}
