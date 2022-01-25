#pragma once

#include <iostream>
#include <vector>
#include "token.h"
#include <sstream>
#include <locale>
#include <iomanip>
#include <chrono>

class Lexer{
    std :: vector <Token> tokens;
public:
    void init_tokens(std :: istream& is);
//    void print_tokens() const;
    size_t get_size() const;
    Token get_token();
};