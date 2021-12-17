#include "editor.h"
#include "buffer.h"

void Editor::execute(std::unique_ptr<EditorCommand> cmd) {
    commands.emplace_back(std::move(cmd));
    auto& last_command = commands.back();
    last_command->execute(text);
    undo_commands.clear();
}

Editor::Editor(TextDocument &text) : text(text){}

void Editor::Undo() {
    if (commands.empty()) {return;}
    commands.back()->undo(text);
    undo_commands.emplace_back(std::move(commands.back()));
    commands.pop_back();
}
void Editor::Redo() {
    if (undo_commands.empty()) {return;}
    undo_commands.back()->execute(text);
    commands.emplace_back(std::move(undo_commands.back()));
    undo_commands.pop_back();
}

void Editor::Save(std::ostream &out) const {
    text.save(out);
}