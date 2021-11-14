#pragma once
#include "text_document.h"
#include "copy.h"
#include "delete.h"
#include "insert.h"
#include "paste.h"
#include "parser.h"
#include <vector>

class Editor final{
    std::vector<std::unique_ptr<EditorCommand>> commands, undo_commands;
    TextDocument& text; // association!
    std::string buffer;
    void add_and_execute(std::unique_ptr<EditorCommand> &&cmd);
public:
    Editor() = delete;
    explicit Editor(TextDocument& text);
    void run(std::istream& in_commands);
    void Copy(const size_t start, const size_t end);
    void Paste(const size_t idx);
    void Insert(std::string&& str, const size_t idx);
    void Delete(const size_t begin, const size_t end);
    void Undo();
    void Redo();
    void Save(std::ostream& out) const;
};