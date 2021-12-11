#pragma once
#include <iostream>
#include <string>

class TextDocument final{
    std::string doc;
public:
    TextDocument() = default;
    TextDocument(const TextDocument& other) = default;
    explicit TextDocument(std::istream& input);
public:
    void insert(const std::string& buffer, const size_t& idx);
    void erase(const size_t& start = 0, const size_t& end = std::string::npos);
    std::string substr(const size_t& start = 0, const size_t& end = std::string::npos) const;
    std::string_view data() const noexcept;
    size_t size() const noexcept;
    void save(std::ostream& out) const;
};