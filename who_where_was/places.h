#pragma once

#include <vector>
#include <string>
#include <map>
#include <fstream>

typedef struct Place{
    std :: string name;
    double x0;
    double y0;
    double x1;
    double y1;
} Place;

class Places{
    std :: vector<Place> places;
public:
    void init_places(std :: istream& is);
    std :: string in_place(double lat, double lon) const;
};