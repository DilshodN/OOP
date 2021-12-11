#include "paste.h"
#include "buffer.h"

PasteCommand::PasteCommand(const size_t &start):start(start){}

void PasteCommand::execute(TextDocument& text) {
    auto buff = Buffer::getInstance();
    text.insert(buff.getBuffer(), start);
}

void PasteCommand::undo(TextDocument& text) {
    text.erase(start, start + Buffer::getInstance().getBuffer().size());
}