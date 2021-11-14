#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-err58-cpp"
#include <gtest/gtest.h>
#include "../sum_all.h"
#include <vector>
#include <string>
#include <list>
#include <map>

using namespace std;

TEST(BasicTest, OneArg){
    EXPECT_EQ(sum_all(3), 3);
    EXPECT_EQ(sum_all('2'), '2');
    EXPECT_EQ(sum_all(3.2), 3.2);
    EXPECT_EQ(sum_all(true), true);
}

TEST(Containers, Vectors){
    vector<int> v1    = { 1, 2, 3 };
    vector<double> v2 = { 1, 2, 3 };
    vector<string> v3 = { "a", "bc", "def" };
    vector<char> v4   = { 'a', 'b', 'c' };
    EXPECT_EQ(sum_all(v1), 6);
    EXPECT_EQ(sum_all(v2), 6.0);
    EXPECT_EQ(sum_all(v3), "abcdef");
    EXPECT_EQ(sum_all(v4), "abc");
}


TEST(Containers, List){
    list<int> v1    = { 1, 2, 3 };
    list<double> v2 = { 1, 2, 3 };
    list<string> v3 = { "a", "bc", "def" };
    list<char> v4   = { 'a', 'b', 'c' };
    EXPECT_EQ(sum_all(v1), 6);
    EXPECT_EQ(sum_all(v2), 6.0);
    EXPECT_EQ(sum_all(v3), "abcdef");
    EXPECT_EQ(sum_all(v4), "abc");
}

TEST(Containers, Map){
    map<int, int> v1    = {{1, 1}, {2, 2}, {3, 3}};
    map<double, double> v2 = {{1, 1}, {2, 2}, {3, 3}};
    map<char, char> v4   = { {'a', 'a'}, {'b', 'b'}, {'c', 'c'}};
    EXPECT_EQ(sum_all(v1), 6);
    EXPECT_EQ(sum_all(v2), 6.0);
    EXPECT_EQ(sum_all(v4), "abc");
}
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

TEST(Containres, OwnClass){
    A a(3);
    A b(4);
    A c(5);
    std::vector<A> v3 = { a, b, c };
    EXPECT_EQ(*sum_all(v3), 12);
    std::map<int, A> m = {{1, a}, {2, b}, {3, c}};
    EXPECT_EQ(*sum_all(m), 12);
}


