#include <iostream>
using namespace std;

const int a(){
    return 1;
}
int main(){
    int b = a();
    b ++;
    cout << b;
    return 0;
}