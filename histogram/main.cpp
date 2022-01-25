#include <iostream>
#include <sstream>
#include "HistogramPlusPlus.h"

using namespace std;

int main(int argc, char* argv[]) {
    if(argc > 3) return 0;

    if(argc == 3) {
        ifstream inp(argv[1]);
        Histogram hist(inp);
        ofstream new_file(argv[2]);
        for(const auto& elem: hist) {
            new_file << elem.first << ": " << string((unsigned long) elem.second, '#') << endl;
        }
        inp.close();
        new_file.close();
        return 0;
    }

    string input;
    getline(cin, input);
    Histogram ht(input);
    for(const auto& elem: ht){
        cout << elem.first << ": " << string((unsigned long)elem.second, '#') << endl;
    }

    return 0;
}