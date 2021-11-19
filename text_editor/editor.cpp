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
    std::vector<CommandDTO> vector_of_dto = CommandParser::parse(in_commands);
    for(const auto& dto: vector_of_dto){
        auto name = dto.get_name();
        switch (name) {
            case Command::COPY:
                this->Copy(dto.get_start(), dto.get_end());
                break;
            case Command::PASTE:
                this->Paste(dto.get_start());
                break;
            case Command::INSERT:
                this->Insert(std::move(dto.get_buff()), dto.get_start());
                break;
            case Command::DELETE:
                this->Delete(dto.get_start(), dto.get_end());
                break;
            case Command::UNDO:
                this->Undo();
                break;
            case Command::REDO:
                this->Redo();
                break;
            case Command::NONE:
                break;
        }
    }
}

