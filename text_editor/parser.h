#pragma once

#include <regex>
#include <map>
#include <sstream>
#include "commands_enum.h"
#include "command_dto.h"

class CommandParser final {
    std::istream& input;
    Command match_command(const std::string &command_name);
public:
    CommandParser() = delete;
    explicit CommandParser(std::istream& input_stream);
    CommandDTO get_next();
};