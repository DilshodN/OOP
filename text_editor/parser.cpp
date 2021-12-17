#include "parser.h"

namespace {
    const std::regex commands_regex = std::regex("copy [0-9]+, [0-9]+|"
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

    CommandDTO parse_undo(std::istringstream &line) {
        return CommandDTO(Command::UNDO);
    }

    CommandDTO parse_redo(std::istringstream &line) {
        return CommandDTO(Command::REDO);
    }

    typedef CommandDTO (*parser_util_function)(std::istringstream &);

    const std::map<std::string, parser_util_function> mapped_util_functions = {{"copy",   parse_copy},
                                                                               {"paste",  parse_paste},
                                                                               {"insert", parse_insert},
                                                                               {"delete", parse_delete},
                                                                               {"undo",   parse_undo},
                                                                               {"redo",   parse_redo}};
}

CommandParser::CommandParser(std::istream &input_stream) : input(input_stream) {}

std::optional<CommandDTO> CommandParser::get_next() {
    std::string buffer;

    if (not std::getline(input, buffer)) {
        return {};
    }

    if (not std::regex_match(buffer, commands_regex)) {
        throw std::invalid_argument("Invalid command");
    }

    std::istringstream line(buffer);
    std::string command_name;
    line >> command_name;

    auto command = mapped_util_functions.at(command_name)(line);
    return command;
}


