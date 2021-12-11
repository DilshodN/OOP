#include "command_dto.h"


CommandDTO::CommandDTO(Command name_of_cmd, const std::string buff, const size_t &idx1, const size_t &idx2)
: cmd_name(name_of_cmd), buff(std::move(buff)), idx1(idx1), idx2(idx2)
{}

std::size_t CommandDTO::get_start() const{
    return idx1;
}

std::size_t CommandDTO::get_end() const{
    return idx2;
}

std::string CommandDTO::get_buff() const{
    return buff;
}

Command CommandDTO::get_name() const{
    return cmd_name;
}



