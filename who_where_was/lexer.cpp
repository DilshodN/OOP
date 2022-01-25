#include "lexer.h"

#define dateTimeFormat "%Y-%m-%dT%H:%M:%S"

namespace {
    time_t parse_time(const char *time) {
        std::istringstream ss{time};
        std::tm dt{};

        if (!(ss >> std::get_time(&dt, dateTimeFormat)) || ss.fail())
            throw std::invalid_argument("wrong time format");

        return std::mktime(&dt);
    }
}


void Lexer ::init_tokens(std :: istream& is) {
    while(not is.eof()){
        std :: string time;
        size_t id;
        double latitude, longitude;
        is >> time >> id >> latitude >> longitude;
        tokens.emplace_back(parse_time(time.c_str()), id, latitude, longitude);
    }
}

size_t Lexer ::get_size() const {
    return tokens.size();
}

Token Lexer ::get_token() {
    if(not tokens.empty()){
        Token temp = tokens.back();
        tokens.pop_back();
        return temp;
    }
    return {0, 0, 0, 0};
}


