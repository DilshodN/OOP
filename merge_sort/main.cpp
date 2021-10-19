#include <iostream>
#include <vector>
#include "msort.h"
#include <algorithm>
#include <list>
struct {
    bool operator()(int a, int b) const { return a < b; }
} customLess;

int main() {
    std::vector<int> v{4, 3, -1, 12, 0, -23, -124124};
    std::list<int> l{4, 3, -1, 12, 0, -23, -124124};

    std::sort(v.begin(), v.end());
    for(const auto& x: v){
        std::cout << x << std :: endl;
    }
    return 0;
}
