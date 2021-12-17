#pragma once
#include "editor_command.h"
#include "commands_enum.h"
class CommandDTO final{
    std::size_t idx1, idx2;
    std::string buff;
    Command cmd_name;
public:
    CommandDTO() = delete;
    CommandDTO(Command name_of_cmd, const std::string buff = "",
               const std::size_t idx1 = 0, const std::size_t idx2 = 0);
    std::size_t get_start() const;
    std::size_t get_end() const;
    std::string get_buff() const;
    Command get_name() const;
};