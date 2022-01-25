#pragma once
#include <iostream>
#include <strstream>
#include <fstream>
#include <sstream>
#include <chrono>


class Token{
    time_t time;
    size_t id;
    double latitude;
    double longitude;

public:
    Token(time_t _time, size_t _id, double _latitude, double _longitude);
//    void print_token() const;
    time_t get_time() const {return time;}
    size_t get_id() const {return id;}
    double get_latitude() const {return latitude;}
    double get_longitude() const {return longitude;}
};