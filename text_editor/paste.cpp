#include "paste.h"
#include "buffer.h"

PasteCommand::PasteCommand(const size_t start):start(start){}

void PasteCommand::execute(TextDocument& text) {
    text.insert(Buffer::getBuffer().read(), start);
}

void PasteCommand::undo(TextDocument& text) {
    text.erase(start, start + Buffer::getBuffer().read().size());
}