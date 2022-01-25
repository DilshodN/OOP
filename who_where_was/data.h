#pragma once

#include <iostream>
#include <map>
#include "lexer.h"
#include "places.h"

class Location{
    time_t time;
    double lat;
    double lon;
public:
    Location(time_t _time, double _lat, double _lon);
    time_t get_time() const { return time;};
    double get_lat() const { return lat;};
    double get_lon() const { return lon;};
    void print_location() const {std ::  cout << lat << " " << lon;};

};


class Data{
    std :: map<size_t, std::vector <Location>> data;
public:
    Data(Lexer& lex);
    void print_data() const;
    std :: string user_path(size_t id, Places pl) const;
};