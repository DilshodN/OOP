#include <iostream>

int main(){
    std::bitset<10> a;
    a.set(0);
//    auto hash = std::hash<int>{}(10);
    std::cout << a.to_string() << std::endl;
    return 0;
}