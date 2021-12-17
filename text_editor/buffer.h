#pragma once
#include <string>


class Buffer{
private:
    std::string buffer;
    Buffer() = default;
    Buffer(Buffer const&) = delete;
    void operator=(Buffer const&) = delete;
public:
    static Buffer& getBuffer();
    const std::string& read() const;
    void write(const std::string& text);
};