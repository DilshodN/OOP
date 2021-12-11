#include "copy.h"
#include "buffer.h"
CopyCommand::CopyCommand(const size_t &start, const size_t &end):
        start(start), end(end){}

void CopyCommand::execute(TextDocument& text) {
    previous_text = Buffer::getInstance().getBuffer();
    auto temp = text.substr(start, end);
    Buffer::getInstance().getBuffer() = temp;
}

void CopyCommand::undo(TextDocument& text) {
    Buffer::getInstance().getBuffer() = previous_text;
}
