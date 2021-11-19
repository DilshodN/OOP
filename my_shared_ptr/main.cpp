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
    std::shared_ptr<int> b(new int(5));
    shared_ptr<int> c(new int(6));
    b = c;

    return 0;
}
