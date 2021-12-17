#include "command_creator.h"

std::unique_ptr<EditorCommand> CommandCreator::try_create_editor_command(const CommandDTO& command_dto) {
    std::unique_ptr<EditorCommand> cmd = nullptr;
    auto name = command_dto.get_name();
    switch (name) {
        case Command::COPY:
            cmd = std::make_unique<CopyCommand>(command_dto.get_start(), command_dto.get_end());
            break;
        case Command::PASTE:
            cmd = std::make_unique<PasteCommand>(command_dto.get_start());
            break;
        case Command::INSERT:
            cmd = std::make_unique<InsertCommand>(command_dto.get_buff(), command_dto.get_start());
            break;
        case Command::DELETE:
            cmd = std::make_unique<DeleteCommand>(command_dto.get_start(), command_dto.get_end());
            break;
        default:
            break;
    }
    return cmd;
}

std::unique_ptr<ServiceCommand> CommandCreator::try_create_service_command(const CommandDTO& command_dto) {
    std::unique_ptr<ServiceCommand> cmd = nullptr;
    auto name = command_dto.get_name();
    switch (name) {
        case Command::UNDO:
            cmd = std::make_unique<UndoCommand>();
            break;
        case Command::REDO:
            cmd = std::make_unique<RedoCommand>();
            break;
        default:
            break;
    }
    return cmd;
}