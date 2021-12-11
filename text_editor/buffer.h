#pragma once
#include <string>

class Buffer;  // опережающее объявление

class BufferDestroyer{
    Buffer* p_instance;
public:
    ~BufferDestroyer();
    void initialize(Buffer* p);
};

class Buffer{
    static Buffer* p_instance;
    static BufferDestroyer destroyer;
    std::string buffer;
protected:
    Buffer() {}
    friend class SingletonDestroyer;
public:
    static Buffer& getInstance();
    std::string& getBuffer();
    ~Buffer() {}
};