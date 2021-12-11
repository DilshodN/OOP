#include "editor_manager.h"

EditorManager::EditorManager(Editor &editor, CommandParser &parser): editor(editor), parser(parser){}

void EditorManager::execute() const {
    while (true) {
        const auto dto_object = parser.get_next();
        if(dto_object.get_name() == Command::NO_COMMAND){
            break;
        }
        auto service_command = CommandCreator::try_create_service_command(dto_object);
        if (service_command) {
            service_command->execute(editor);
        }

        auto editor_command = CommandCreator::try_create_editor_command(dto_object);
        if (editor_command) {
            editor.execute(std::move(editor_command));
        }
    }
}

