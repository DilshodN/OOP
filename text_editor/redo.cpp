#include "redo.h"

void RedoCommand::execute(Editor& editor) const {
    editor.Redo();
}
