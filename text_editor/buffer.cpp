#include "buffer.h"


Buffer &Buffer::getBuffer() {
    static Buffer instance;
    return instance;
}

void Buffer::write(const std::string& text) {
    buffer = text;
}

const std::string &Buffer::read() const {
    return buffer;
}