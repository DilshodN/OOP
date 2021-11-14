#pragma once
#include <regex>
#include <string>
#include <sstream>
#include "editor.h"
#include "commands_enum.h"
class Editor;

class CommandParser final{
    static inline const std::regex commands_regex =
           std::regex("copy [0-9]+, [0-9]+|"
                      "paste [0-9]+|"
                      "insert \"[^ \f\n\r\t\v]+\", [0-9]+|"
                      "delete [0-9]+, [0-9]+|"
                      "undo|"
                      "redo") ;

    static Command match_command(const std::string& command_name);
public:
    CommandParser() = delete;
    static void parse(Editor* editor, std::istream& input);
};