#include "parser.h"

namespace {
    void parse_copy(Editor *editor, std::istringstream &line) {
        std::string start, end;
        line >> start;
        start.erase(start.size() - 1, 1);
        line >> end;
        editor->Copy(std::stoul(start), std::stoul(end));
    }

    void parse_paste(Editor *editor, std::istringstream &line) {
        std::string start;
        line >> start;
        editor->Paste(std::stoul(start));
    }

    void parse_insert(Editor *editor, std::istringstream &line) {
        std::string text_of_insert, idx;
        line >> text_of_insert;
        line >> idx;
        // "Hello, there", -> Hello, there
        text_of_insert.erase(0, 1);
        text_of_insert.erase(text_of_insert.size() - 2, 2);
        editor->Insert(std::move(text_of_insert), std::stoul(idx));
    }

    void parse_delete(Editor *editor, std::istringstream &line) {
        std::string start, end;
        line >> start;
        start.erase(start.size() - 1, 1);
        line >> end;
        editor->Delete(std::stoul(start), std::stoul(end));
    }
}

void CommandParser::parse(Editor* editor, std::istream &input){
    std::string buffer;
    while(std::getline(input, buffer)){
        if(not std::regex_match(buffer, commands_regex)){
            throw std::invalid_argument("Invalid command");
        }
        std::istringstream line(buffer);
        std::string command_name;
        line >> command_name;
        Command cmd = match_command(command_name);
        switch (cmd) {
            case Command::COPY:
                parse_copy(editor, line);
                break;
            case Command::PASTE:
                parse_paste(editor, line);
                break;
            case Command::INSERT:
                parse_insert(editor, line);
                break;
            case Command::DELETE:
                parse_delete(editor, line);
                break;
            case Command::UNDO:
                editor->Undo();
                break;
            case Command::REDO:
                editor->Redo();
                break;
            case Command::NONE:
                break;
        }
    }
}

Command CommandParser::match_command(const std::string &command_name) {
    if(command_name == "copy") {
        return Command::COPY;
    }
    if(command_name == "paste") {
        return Command::PASTE;
    }
    if(command_name == "insert") {
        return Command::INSERT;
    }
    if(command_name == "delete") {
        return Command::DELETE;
    }
    if(command_name == "undo") {
        return Command::UNDO;
    }
    if(command_name == "redo") {
        return Command::REDO;
    }
    return Command::NONE;
}
