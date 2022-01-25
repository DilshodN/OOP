#include <iostream>
#include "token.h"
#include <vector>
#include "lexer.h"
#include "data.h"
#include "places.h"
using namespace std;

int main(int argc, char * argv[]) {
    if(argc >= 5){
        try {
            ifstream logs(argv[1]);
            Lexer l;
            l.init_tokens(logs);
            Data d(l);

            ifstream places(argv[2]);
            Places pl;
            pl.init_places(places);

            ofstream write_file(argv[4]);
            int id = stoi(argv[3]);

            write_file << d.user_path(id, pl);
            logs.close();
            places.close();
            write_file.close();
        }
        catch (exception& e){
            cout << "Invalud Input";
        }
    }
    else {
        cout << "Invalid Input";
    }
    return 0;
}