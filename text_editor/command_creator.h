#pragma once
#include <vector>

#include "editor_command.h"
#include "copy.h"
#include "delete.h"
#include "insert.h"
#include "paste.h"
#include "parser.h"
#include "command_dto.h"
#include "service_command.h"
#include "undo.h"
#include "redo.h"

class CommandCreator final{
public:
    static std::unique_ptr<EditorCommand> try_create_editor_command(const CommandDTO& command_dto);
    static std::unique_ptr<ServiceCommand> try_create_service_command(const CommandDTO& command_dto);
};