#include "data.h"

namespace {
    struct{
        bool operator()(Location a, Location b){
            return a.get_time() > b.get_time();
        }
    }TimeComp;
}

Location ::Location(time_t _time, double _lat, double _lon) {
    time = _time;
    lat = _lat;
    lon = _lon;
}

Data::Data(Lexer& lex) {
    while (lex.get_size() != 0) {
        Token t = lex.get_token();
        data[t.get_id()].emplace_back(t.get_time(), t.get_latitude(), t.get_longitude());
    }
    for (auto& user: data)
        std::sort(user.second.begin(), user.second.end(), TimeComp);
}

void Data ::print_data() const {
    for (const auto& user : data){
        std :: cout << user.first << std :: endl;
        for(auto m: user.second){
            m.print_location();
            std :: cout << std  :: endl;
        }
    }
}

std :: string Data :: user_path(size_t id, Places pl) const{
    std :: ostringstream path;
    auto user_found = data.find(id);
    if(user_found == data.end()) {
        path << "No matching user";
        return path.str();
    }

    else{
        path << "User id: " << id << " path:" << std :: endl;
        auto locs = data.at(id);
        for(const auto& loc : locs){
            path << pl.in_place(loc.get_lat(), loc.get_lon()) << "->";
        }
    }
    path << "Finish";
    return path.str();
}