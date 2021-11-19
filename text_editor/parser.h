#pragma once

#include <regex>
#include <string>
#include <sstream>
#include <map>
#include <algorithm>
#include "editor.h"
#include "commands_enum.h"
#include "command_dto.h"

class Editor;

class CommandParser final {
    static inline const std::map<std::string, Command> table_of_commands = {{"copy",   Command::COPY},
                                                                            {"paste",  Command::PASTE},
                                                                            {"insert", Command::INSERT},
                                                                            {"delete", Command::DELETE},
                                                                            {"undo",   Command::UNDO},
                                                                            {"redo",   Command::REDO},
                                                                            {"delete", Command::DELETE}};
    static inline const std::regex commands_regex =
            std::regex("copy [0-9]+, [0-9]+|"
                       "paste [0-9]+|"
                       "insert \"[^ \f\n\r\t\v]+\", [0-9]+|"
                       "delete [0-9]+, [0-9]+|"
                       "undo|"
                       "redo");

    static Command match_command(const std::string &command_name);

public:
    CommandParser() = delete;

    static std::vector<CommandDTO> parse(std::istream &input);
};