#include "parser.h"

namespace {

    const std::map<std::string, Command> table_of_commands = {{"copy",   Command::COPY},
                                                              {"paste",  Command::PASTE},
                                                              {"insert", Command::INSERT},
                                                              {"delete", Command::DELETE},
                                                              {"undo",   Command::UNDO},
                                                              {"redo",   Command::REDO},
                                                              {"delete", Command::DELETE}};

    const std::regex commands_regex =std::regex("copy [0-9]+, [0-9]+|"
                                                    "paste [0-9]+|"
                                                    "insert \"[^ \f\n\r\t\v]+\", [0-9]+|"
                                                    "delete [0-9]+, [0-9]+|"
                                                    "undo|"
                                                    "redo");

    CommandDTO parse_copy(std::istringstream &line) {
        std::string start, end;
        line >> start;
        start.erase(start.size() - 1, 1);
        line >> end;
        return CommandDTO(Command::COPY, "", std::stoul(start), std::stoul(end));
    }

    CommandDTO parse_paste(std::istringstream &line) {
        std::string start;
        line >> start;
        return CommandDTO(Command::PASTE, "", std::stoul(start));
    }

    CommandDTO parse_insert(std::istringstream &line) {
        std::string text_of_insert, idx;
        line >> text_of_insert;
        line >> idx;
        // "Hello, there", -> Hello, there
        text_of_insert.erase(0, 1);
        text_of_insert.erase(text_of_insert.size() - 2, 2);
        return CommandDTO(Command::INSERT, std::move(text_of_insert), std::stoul(idx));
    }

    CommandDTO parse_delete(std::istringstream &line) {
        std::string start, end;
        line >> start;
        start.erase(start.size() - 1, 1);
        line >> end;
        return CommandDTO(Command::DELETE, "", std::stoul(start), std::stoul(end));
    }

    CommandDTO parse_undo() {
        return CommandDTO(Command::UNDO);
    }

    CommandDTO parse_redo() {
        return CommandDTO(Command::REDO);
    }
}

CommandParser::CommandParser(std::istream &input_stream): input(input_stream) {}

CommandDTO CommandParser::get_next() {
    CommandDTO command;

    std::string buffer;

    if(not std::getline(input, buffer)){
        return CommandDTO(Command::NO_COMMAND);
    }

    if (not std::regex_match(buffer, commands_regex)) {
        throw std::invalid_argument("Invalid command");
    }

    std::istringstream line(buffer);
    std::string command_name;
    line >> command_name;

    Command cmd = match_command(command_name);
    switch (cmd) {
        case Command::COPY:
            command = std::move(parse_copy(line));
            break;
        case Command::PASTE:
            command = std::move(parse_paste(line));
            break;
        case Command::INSERT:
            command = std::move(parse_insert(line));
            break;
        case Command::DELETE:
            command = std::move(parse_delete(line));
            break;
        case Command::UNDO:
            command = std::move(parse_undo());
            break;
        case Command::REDO:
            command = std::move(parse_redo());
            break;
        default:
            break;
    }
    return command;
}

Command CommandParser::match_command(const std::string &command_name) {
    return table_of_commands.contains(command_name) ? table_of_commands.at(command_name) : Command::NONE;
}


