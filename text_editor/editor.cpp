#include "editor.h"

void Editor::add_and_execute(std::unique_ptr<EditorCommand> &&cmd) {
    commands.emplace_back(std::move(cmd));
    commands.back()->execute();
    undo_commands.clear();
}

Editor::Editor(TextDocument& text): text(text){}

void Editor::Copy(const size_t start, const size_t end) {
    add_and_execute(std::make_unique<CopyCommand>(text, buffer, start, end));
}

void Editor::Paste(const size_t start) {
    add_and_execute(std::make_unique<PasteCommand>(text, buffer, start));
}

void Editor::Insert(std::string &&str, const size_t start) {
    add_and_execute(std::make_unique<InsertCommand>(text, std::move(str), start));
}

void Editor::Delete(const size_t start, const size_t end) {
    add_and_execute(std::make_unique<DeleteCommand>(text, start, end));
}

void Editor::Undo() {
    if (commands.empty()) {return;}
    commands.back()->undo();
    undo_commands.emplace_back(std::move(commands.back()));
    commands.pop_back();
}
void Editor::Redo() {
    if (undo_commands.empty()) {return;}
    undo_commands.back()->execute();
    commands.emplace_back(std::move(undo_commands.back()));
    undo_commands.pop_back();
}
void Editor::Save(std::ostream &out) const {
    text.save(out);
}

void Editor::run(std::istream &in_commands) {
    CommandParser::parse(this, in_commands);
}

