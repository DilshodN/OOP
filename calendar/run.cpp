#include "run.h"
#include <fstream>
#include <iostream>
#include <regex>
#include "calendar.h"


using namespace std;

namespace {
    vector<string> modes = {"month", "year", "range"};
    vector<string> features = {"vert", "horiz", "year_for_every_month", "year_once"};

    bool str_in_modes(string &s) {
        return find(modes.begin(), modes.end(), s) != modes.end();
    }

    bool str_in_feats(string &s) {
        return find(features.begin(), features.end(), s) != features.end();
    }

    enum modes {
        month,
        year,
        range
    };

    enum features {
        vert = 0,
        horiz,
        year_for_every_month,
        year_once
    };

    long int get_mode(string &s) {
        auto it = find(modes.begin(), modes.end(), s);
        long int idx = distance(modes.begin(), it);
        return idx;
    }

    long int get_feat(string &s) {
        auto it = find(features.begin(), features.end(), s);
        long int idx = distance(features.begin(), it);
        return idx;
    }

    bool isNumber(const string &str) {
        for (char const &c : str) {
            if (isdigit(c) == 0) return false;
        }
        return true;
    }

    void parse_month(istream &file, args *arg) {
        string temp;
        getline(file, temp, ' ');
        if (!isNumber(temp) || temp.empty()) {
            arg->flag_error = true;
            return;
        }
        int year = stoi(temp);

        if (year <= 0) {
            arg->flag_error = true;
            return;
        }

        arg->year1 = year;
        arg->year2 = year;

        getline(file, temp, ' ');
        if (!isNumber(temp) || temp.empty()) {
            arg->flag_error = true;
            return;
        }

        int month = stoi(temp);

        if (month <= 0 || month > 12) {
            arg->flag_error = true;
            return;
        }

        arg->month1 = month;
        arg->month2 = month;
    }

    void parse_year(istream &file, args *arg) {
        string temp;
        getline(file, temp, ' ');
        if (!isNumber(temp) || temp.empty()) {
            arg->flag_error = true;
            return;
        }
        int year = stoi(temp);

        if (year <= 0) {
            arg->flag_error = true;
            return;
        }

        arg->year1 = year;
        arg->year2 = year;
        arg->month1 = 1;
        arg->month2 = 12;
    }

    void parse_range(istream &file, args *arg) {
        string temp;
        getline(file, temp, ' ');

        if (!isNumber(temp) || temp.empty()) {
            arg->flag_error = true;
            return;
        }

        int month1 = stoi(temp);

        if (month1 <= 0 || month1 > 12) {
            arg->flag_error = true;
            return;
        }

        arg->month1 = month1;

        getline(file, temp, ' ');

        if (!isNumber(temp) || temp.empty()) {
            arg->flag_error = true;
            return;
        }

        int year1 = stoi(temp);

        if (year1 <= 0) {
            arg->flag_error = true;
            return;
        }

        arg->year1 = year1;

        getline(file, temp, ' ');
        if (!isNumber(temp) || temp.empty()) {
            arg->flag_error = true;
            return;
        }

        int month2 = stoi(temp);

        if (month2 <= 0 || month2 > 12) {
            arg->flag_error = true;
            return;
        }

        arg->month2 = month2;

        getline(file, temp, ' ');
        if (!isNumber(temp) || temp.empty()) {
            arg->flag_error = true;
            return;
        }

        int year2 = stoi(temp);

        if (year2 <= 0 || year2 < year1 || (year1 == year2 && month1 > month2)) {
            arg->flag_error = true;
            return;
        }


        arg->year2 = year2;
    }

    void parse_features(istream &file, args *arg) {
        string temp;
        getline(file, temp, ' ');
        if (!(temp == "|")) {
            arg->flag_error = true;
            return;
        }
        getline(file, temp, ' ');

        if (!str_in_feats(temp) || (get_feat(temp) != vert && get_feat(temp) != horiz)) {
            arg->flag_error = true;
            return;
        }
        if (get_feat(temp) == vert) {
            arg->vert = true;
            arg->horiz = false;
        }

        if (get_feat(temp) == horiz) {
            arg->vert = false;
            arg->horiz = true;
        }

        getline(file, temp, ' ');

        if (!str_in_feats(temp) || (get_feat(temp) != year_once && get_feat(temp) != year_for_every_month)) {
            arg->flag_error = true;
            return;
        }
        if (get_feat(temp) == year_once) {
            arg->year_once = true;
            arg->year_for_every_month = false;
        }

        if (get_feat(temp) == year_for_every_month) {
            arg->year_for_every_month = true;
            arg->year_once = false;
        }
    }
}

args parsefile(istream& file){
    args arg;
    arg.flag_error = false;
    string temp;
    getline(file, temp, ' ');
    if(temp.empty() || !str_in_modes(temp)){
        arg.flag_error = true;
        return arg;
    }

    switch(get_mode(temp)){
        case month:
            parse_month(file, &arg);
            parse_features(file, &arg);
            break;
        case year:
            parse_year(file, &arg);
            parse_features(file, &arg);
            break;
        case range:
            parse_range(file, &arg);
            parse_features(file, &arg);
            break;
        default:
            arg.flag_error = true;
            break;
    }
    temp.clear();
    getline(file, temp);
    if(!temp.empty()){
        arg.flag_error = true;
        return arg;
    }
    return arg;
}