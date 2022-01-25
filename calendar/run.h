#pragma once

#include <iostream>


typedef struct args {
    int month1;
    int year1;
    int month2;
    int year2;

    bool vert;
    bool horiz;
    bool year_for_every_month;
    bool year_once;

    bool flag_error;
} args;

args parsefile(std::istream& file);