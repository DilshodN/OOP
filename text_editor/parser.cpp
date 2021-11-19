#include "parser.h"

namespace {
    void parse_copy(std::vector<CommandDTO>& commands, std::istringstream &line) {
        std::string start, end;
        line >> start;
        start.erase(start.size() - 1, 1);
        line >> end;
        commands.emplace_back(Command::COPY, "", std::stoul(start), std::stoul(end));
    }

    void parse_paste(std::vector<CommandDTO>& commands, std::istringstream &line) {
        std::string start;
        line >> start;
        commands.emplace_back(Command::PASTE, "", std::stoul(start));
    }

    void parse_insert(std::vector<CommandDTO>& commands, std::istringstream &line) {
        std::string text_of_insert, idx;
        line >> text_of_insert;
        line >> idx;
        // "Hello, there", -> Hello, there
        text_of_insert.erase(0, 1);
        text_of_insert.erase(text_of_insert.size() - 2, 2);
        commands.emplace_back(Command::INSERT, std::move(text_of_insert), std::stoul(idx));
    }

    void parse_delete(std::vector<CommandDTO>& commands, std::istringstream &line) {
        std::string start, end;
        line >> start;
        start.erase(start.size() - 1, 1);
        line >> end;
        commands.emplace_back(Command::DELETE, "", std::stoul(start), std::stoul(end));
    }
    void parse_undo(std::vector<CommandDTO>& commands){
        commands.emplace_back(Command::UNDO);
    }
    void parse_redo(std::vector<CommandDTO>& commands){
        commands.emplace_back(Command::REDO);
    }
}

std::vector<CommandDTO> CommandParser::parse(std::istream &input) {
    std::string buffer;
    std::vector<CommandDTO> commands;
    while (std::getline(input, buffer)) {
        if (not std::regex_match(buffer, commands_regex)) {
            throw std::invalid_argument("Invalid command");
        }
        std::istringstream line(buffer);
        std::string command_name;
        line >> command_name;
        Command cmd = match_command(command_name);
        switch (cmd) {
            case Command::COPY:
                parse_copy(commands, line);
                break;
            case Command::PASTE:
                parse_paste(commands, line);
                break;
            case Command::INSERT:
                parse_insert(commands, line);
                break;
            case Command::DELETE:
                parse_delete(commands, line);
                break;
            case Command::UNDO:
                parse_undo(commands);
                break;
            case Command::REDO:
                parse_redo(commands);
                break;
            case Command::NONE:
                break;
        }
    }
    return commands;
}

Command CommandParser::match_command(const std::string &command_name) {
    return table_of_commands.contains(command_name) ? table_of_commands.at(command_name) : Command::NONE;
}
