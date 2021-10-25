#include <iostream>
#include "shared_ptr.h"

using namespace std;
class T{
public:
    ~T(){
        cout << "~T()" << endl;
    }
};

int main() {

    SharedPTR<T> a(new T);
//    SharedPTR<T[]> b(new T[10]);
    return 0;
}
