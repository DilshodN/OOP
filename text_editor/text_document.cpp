#include "text_document.h"

TextDocument::TextDocument(std::istream &input) {
    getline(input, doc);
}

void TextDocument::insert(const std::string &buffer, const size_t& idx) {
    idx < size() ? doc.insert(idx, buffer) : doc.insert(size(), buffer);
}

void TextDocument::erase(const size_t &start, const size_t &end) {
    if(doc.empty()) return;
    start <= size() and start <= end ? doc.erase(start, end - start) : throw std::out_of_range("Erase error");
}

std::string TextDocument::substr(const size_t &start, const size_t &end) const {
    return start <= size() and start <= end and not doc.empty() ? doc.substr(start, end - start) : std::string{};
}

std::string_view TextDocument::data() const noexcept{
    return doc;
}

size_t TextDocument::size() const noexcept{
    return doc.size();
}

void TextDocument::save(std::ostream &out) const {
    out << doc;
}

