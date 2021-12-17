#pragma once

#include <regex>
#include <map>
#include <sstream>
#include <string>
#include "commands_enum.h"
#include "command_dto.h"

class CommandParser final {
    std::istream& input;
public:
    CommandParser() = delete;
    explicit CommandParser(std::istream& input_stream);
    std::optional<CommandDTO> get_next();
};