#include <gtest/gtest.h>
#include "../msort.h"
#include <array>
#include <deque>
#include <list>
struct {
    bool operator()(int a, int b) const { return a < b; }
} customLess;

using namespace std;
TEST(MergeSortWithCmp, SortVector) {
    vector<int> shuffle = {2, 4, 1, 5, 0, 3};
    vector<int> test = {0, 1, 2, 3, 4, 5};
    A::msort(shuffle.begin(), shuffle.end(), customLess);
    EXPECT_EQ(test, shuffle);
}
TEST(MergeSortWithCmp, SortArray) {
    array<int, 6> shuffle = {2, 4, 1, 5, 0, 3};
    array<int, 6> test = {0, 1, 2, 3, 4, 5};
    A::msort(shuffle.begin(), shuffle.end(), customLess);
    EXPECT_EQ(test, shuffle);

    list<int> abc;
    EXPECT_NO_FATAL_FAILURE(A::msort(abc.begin(), abc.end(), customLess));

}

TEST(MergeSortWithCmp, SortDeque) {
    deque<int> shuffle = {2, 4, 1, 5, 0, 3};
    deque<int> test = {0, 1, 2, 3, 4, 5};
    A::msort(shuffle.begin(), shuffle.end(), customLess);
    EXPECT_EQ(test, shuffle);
}
