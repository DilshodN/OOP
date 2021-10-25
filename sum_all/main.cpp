#include <iostream>
#include <vector>
#include "sum_all.h"

using namespace std;
class A{
    int k;
public:
    A() = default;
    explicit A(int l) : k(l){};
    A& operator=(const A& other) = default; // copy assignable
    A& operator+=(const A& rhs){
        k += rhs.k;
        return *this;
    }
    A operator+(const A& rhs) const{
        A temp{};
        temp.k = k + rhs.k;
        return temp;
    }
    int operator*() const{
        return k;
    }
};

int main() {
    A a(3);
    A b(4);
    A c(5);
    std::vector<A> v3 = { a, b, c };
    cout << *sum_all(v3);
    return 0;
}
