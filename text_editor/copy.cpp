#include "copy.h"
#include "buffer.h"
CopyCommand::CopyCommand(const size_t start, const size_t end):
        start(start), end(end){}

void CopyCommand::execute(TextDocument& text) {
    previous_text = Buffer::getBuffer().read();
    auto temp = text.substr(start, end);
    Buffer::getBuffer().write(temp);
}

void CopyCommand::undo(TextDocument& text) {
    Buffer::getBuffer().write(previous_text);
}
