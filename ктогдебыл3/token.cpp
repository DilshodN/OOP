#include "token.h"

//void Token ::print_token() const {
//    std :: cout << time << " " << id << " " << latitude << " " << longitude << std :: endl;
//}

Token ::Token(time_t _time, size_t _id, double _latitude, double _longitude) {
    time = _time;
    id  = _id;
    latitude = _latitude;
    longitude = _longitude;
}


