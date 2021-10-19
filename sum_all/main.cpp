#include <iostream>
#include <string>
#include <vector>
#include "sum_all.h"
using namespace std;

int main() {
    A a(3);
    A b(4);
    A c(5);
    vector<A> v3 = { a, b, c };

    cout << sum_all(v3);
    return 0;
}
