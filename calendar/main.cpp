#include <iostream>
#include "calendar.h"
#include <fstream>
#include "run.h"



using namespace std;

int main(int argc, char* argv[]) {
    if(argc >= 2) {
        ifstream inp(argv[1]);
        if(inp){
            stringstream stream;
            stream << inp.rdbuf();
            inp.close();
            args arguments = parsefile(stream);
            if(!arguments.flag_error) {
                int orient = arguments.horiz ? 0 : 1;
                cout << print_date(arguments.month1, arguments.year1, arguments.month2, arguments.year2,
                                   arguments.year_for_every_month, arguments.year_once, orient);
            }
        }
        return 0;
    }
    string input;
    getline(cin, input);
    stringstream ss(input);
    args arguments = parsefile(ss);
    int orient = arguments.horiz ? 0 : 1;
    cout << print_date(arguments.month1, arguments.year1, arguments.month2, arguments.year2,
                       arguments.year_for_every_month, arguments.year_once, orient);
    return 0;
}
