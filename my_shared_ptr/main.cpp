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
    SharedPTR<int> a = make_shared_ptr<int>(5);
//    a = b;
    a.reset(new int(6));
    cout << *a << endl;

    return 0;
}
