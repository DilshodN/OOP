#include <iostream>

template<int...args>
int sum(){
    return (0 + ... + args);
}

int main(){
    std::cout << sum<1, 2, 3>() << std::endl;
    return 0;
}