#include <iostream>
#include "shared_ptr.h"
#include <memory>

using namespace std;
class T{
public:
    ~T(){
        cout << "~T()" << endl;
    }
};

int main() {
    SharedPTR<T[]> a(new T[10]);

    return 0;
}
