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

TEST(ContainersTest, Vectors){
    vector<int> v1    = { 1, 2, 3 };
    vector<double> v2 = { 1, 2, 3 };
    vector<string> v3 = { "a", "bc", "def" };
    vector<char> v4   = { 'a', 'b', 'c' };
    EXPECT_EQ(sum_all(v1), 6);
    EXPECT_EQ(sum_all(v2), 6.0);
    EXPECT_EQ(sum_all(v3), "abcdef");
    EXPECT_EQ(sum_all(v4), "abc");
}


TEST(ContainersTest, List){
    list<int> v1    = { 1, 2, 3 };
    list<double> v2 = { 1, 2, 3 };
    list<string> v3 = { "a", "bc", "def" };
    list<char> v4   = { 'a', 'b', 'c' };
    EXPECT_EQ(sum_all(v1), 6);
    EXPECT_EQ(sum_all(v2), 6.0);
    EXPECT_EQ(sum_all(v3), "abcdef");
    EXPECT_EQ(sum_all(v4), "abc");
}

TEST(ContainersTest, Map){
    map<int, int> v1    = {{1, 1}, {2, 2}, {3, 3}};
    map<double, double> v2 = {{1, 1}, {2, 2}, {3, 3}};
    map<char, char> v4   = { {'a', 'a'}, {'b', 'b'}, {'c', 'c'}};
    EXPECT_EQ(sum_all(v1), 6);
    EXPECT_EQ(sum_all(v2), 6.0);
    EXPECT_EQ(sum_all(v4), "abc");
}

