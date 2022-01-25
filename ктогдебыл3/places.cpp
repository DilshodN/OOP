#include "places.h"


Place create_place(std :: string& _name, double _x0, double _y0, double _x1, double _y1){
    Place a;
    a.name = _name;
    a.x0 = _x0;
    a.y0 = _y0;
    a.x1 = _x1;
    a.y1 = _y1;
    return a;
}

void Places ::init_places(std::istream &is) {
    while(not is.eof()){
        std :: string name;
        double x0, y0, x1, y1;
        is >> name >> x0 >> y0 >> x1 >> y1;
        places.push_back(create_place(name, x0, y0, x1, y1));
    }
}

std :: string Places::in_place(double lat, double lon) const{
    for(const auto& place: places){
        double x_min = place.x0 < place.x1 ? place.x0 : place.x1;
        double y_min = place.y0 < place.y1 ? place.y0 : place.y1;
        double x_max = place.x0 > place.x1 ? place.x0 : place.x1;
        double y_max = place.y0 > place.y1 ? place.y0 : place.y1;
        if(x_min <= lat and x_max >= lat and y_min <= lon and y_max >= lon)
            return place.name;
    }
    return "[Unknown Place]";
}
