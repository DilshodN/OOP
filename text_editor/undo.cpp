#include "undo.h"

void UndoCommand::execute(Editor& editor) const {
    editor.Undo();
}


