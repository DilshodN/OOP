#include "HistogramPlusPlus.h"

using namespace std;

Histogram::Histogram(std::istream &is) {
    string word;
    while (is >> word) {
        ht[word]++;
    }
}

Histogram::Histogram(const string &str) {
    string word;
    istringstream ss(str);
    while (ss >> word) {
        ht[word]++;
    }
}

Histogram::Histogram(const vector<string> &v) {
    for (const auto &str: v) {
        ht[str]++;
    }
}

Histogram Histogram::operator+(const Histogram &another) const {
    Histogram new_ht(*this);
    for (const auto &elem: another.ht) {
        new_ht.ht[elem.first] += elem.second;
        if (new_ht.ht[elem.first] == 0) {
            new_ht.ht.erase(elem.first);
        }
    }
    return new_ht;
}

Histogram Histogram::operator-(const Histogram &another) const {
    Histogram new_ht(*this);
    for (const auto &elem: another.ht) {
        new_ht.ht[elem.first] -= elem.second;
        if (new_ht.ht[elem.first] == 0) {
            new_ht.ht.erase(elem.first);
        }
    }
    return new_ht;
}

bool Histogram::operator==(const Histogram &another) const {
    if (ht.size() != another.ht.size()) return false;

    for (const auto &elem: another.ht) {
        auto it = ht.find(elem.first);
        if (it == ht.end()) return false;

        else {
            if (it->second != elem.second) return false;
        }
    }
    return true;
}

const std::map<std::string, int>& Histogram::data() const{
    return ht;
}


Histogram::iterator Histogram::begin() {
    return ht.begin();
}

Histogram::iterator Histogram::end() {
    return ht.end();
}

std::map<std::string, int>::const_iterator Histogram::cbegin() const {
    return ht.cbegin();
}

std::map<std::string, int>::const_iterator Histogram::cend() const {
    return ht.cend();
}