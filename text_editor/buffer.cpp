#include "buffer.h"


Buffer* Buffer::p_instance = 0;
BufferDestroyer Buffer::destroyer;

BufferDestroyer::~BufferDestroyer() {
    delete p_instance;
}

void BufferDestroyer::initialize( Buffer* p ) {
    p_instance = p;
}
Buffer& Buffer::getInstance() {
    if(!p_instance)     {
        p_instance = new Buffer();
        destroyer.initialize( p_instance);
    }
    return *p_instance;
}

std::string &Buffer::getBuffer() {
    return buffer;
}
