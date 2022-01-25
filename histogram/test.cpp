#include <gtest/gtest.h>
#include "../HistogramPlusPlus.h"

using namespace std;

TEST(Constructors, ConstructorStringEmpty) {
    EXPECT_NO_THROW(Histogram(""));
    EXPECT_NO_THROW(Histogram("    "));
}

TEST(Construcors, ConstructorVectorEmpty) {
    vector<string> v{};
    EXPECT_NO_THROW(Histogram(v));
}

TEST(Construcors, ConstructorStreamEmpty) {
    const string s = "";
    istringstream iss(s);
    EXPECT_NO_THROW(Histogram(iss));
}

TEST(Constructors, ConstructorRepeatString) {
    map<string, int> mp1;
    mp1["a"] = 3;
    mp1["b"] = 2;
    mp1["c"] = 3;
    mp1["z"] = 2;

    string word1 = "a a a b b c c c z z";

    Histogram ht1(word1);
    EXPECT_EQ(mp1, ht1.data());
}

TEST(Constructors, ConstructorNoRepeatString){
    map<string, int> mp2;
    for (int i = 1; i < 7; i++) {
        mp2[to_string(i)] = 1;
    }

    string word2 = "1 2 3 4 5 6";

    Histogram ht2(word2);
    EXPECT_EQ(mp2, ht2.data());
}

TEST(Constructors, ConstructorVectorRepeat) {

    map<string, int> mp1;
    mp1["a"] = 3;
    mp1["b"] = 2;
    mp1["c"] = 3;
    mp1["z"] = 2;

    const vector<string> v1 = {"a", "a", "a", "b", "b", "c", "c", "c", "z", "z"};

    Histogram ht1(v1);
    EXPECT_EQ(mp1, ht1.data());
}
TEST(Constructors, ConstructorVectorNoRepeat)
{
    map<string, int> mp2;
    for (int i = 1; i < 7; i++) {
        mp2[to_string(i)] = 1;
    }

    const vector<string> v2 = {"1", "2", "3", "4", "5", "6"};

    Histogram ht2(v2);
    EXPECT_EQ(mp2, ht2.data());
}

TEST(Constructors, ConstructorStreamRepeat) {

    map<string, int> mp1;
    mp1["a"] = 3;
    mp1["b"] = 2;
    mp1["c"] = 3;
    mp1["z"] = 2;

    istringstream iss1("a a a b b c c c z z");

    Histogram ht1(iss1);
    EXPECT_EQ(mp1, ht1.data());
}
TEST(Constructors, ConstructorStreamNoRepeat)
{
    map<string, int> mp2;
    for (int i = 1; i < 7; i++) {
        mp2[to_string(i)] = 1;
    }

    istringstream iss2("1 2 3 4 5 6");

    Histogram ht2(iss2);
    EXPECT_EQ(mp2, ht2.data());
}

TEST(Operators, PlusNoRepeat) {
    string w1 = "1 2 3";
    Histogram ht1(w1);

    string w2 = "4 5 6";
    Histogram ht2(w2);

    Histogram ht_sum = ht1 + ht2;

    map<string, int> mp1 = ht_sum.data();

    EXPECT_EQ(mp1["1"], 1);
    EXPECT_EQ(mp1["2"], 1);
    EXPECT_EQ(mp1["3"], 1);
    EXPECT_EQ(mp1["4"], 1);
    EXPECT_EQ(mp1["5"], 1);
    EXPECT_EQ(mp1["6"], 1);
}
TEST(Operators, PlusRepeat){
    string w3 = "1 1 1 1 2 3 3 44 4 44 4 43 3 2 1";
    Histogram ht3(w3);

    string w4 = "1 1 1 3 44 3";
    Histogram ht4(w4);

    Histogram ht_sum2 = ht3 + ht4;

    map<string, int> mp2 = ht_sum2.data();

    EXPECT_EQ(mp2["1"], 8);
    EXPECT_EQ(mp2["2"], 2);
    EXPECT_EQ(mp2["3"], 5);
    EXPECT_EQ(mp2["4"], 2);
    EXPECT_EQ(mp2["43"], 1);
    EXPECT_EQ(mp2["44"], 3);
}


TEST(Operators, MinusEmptyHist) {
    Histogram h1("a");
    Histogram h2("a");

    Histogram h_ = h1 - h2;
    ASSERT_TRUE(h_.data().empty());
}

TEST(Operators, MinusRepeat){

    string a = "1 1 1 1 2 3 3 44 4 44 4 43 3 2 1";
    Histogram ht1(a);

    string b = "1 1 1 3 44 3 43";
    Histogram ht2(b);

    Histogram ht3 = ht1 - ht2;

    map<string, int> mp = ht3.data();

    EXPECT_EQ(mp["1"], 2);
    EXPECT_EQ(mp["2"], 2);
    EXPECT_EQ(mp["3"], 1);
    EXPECT_EQ(mp["4"], 2);
    EXPECT_EQ(mp["44"], 1);
}

TEST(Operators, Equal){
    Histogram h1("a b c");
    Histogram h2("a b c");
    ASSERT_TRUE(h1 == h2);
}

TEST(Operators, NotEqual){
    Histogram h1("a 2 c");
    Histogram h2("a b c");
    ASSERT_FALSE(h1 == h2);
}

TEST(Operators, AllMethods) {
    Histogram h1("a");
    Histogram h3("b");
    ASSERT_FALSE(h1 == h3);

    h3 = h1 + h3;

    Histogram h4("a b");
    ASSERT_TRUE(h3 == h4);

    Histogram h5 = h3 + h4;
    map<string, int> m = h5.data();
    EXPECT_EQ(m["a"], 2);
    EXPECT_EQ(m["b"], 2);

    h5 = h5 - h3 - h3;
    ASSERT_TRUE(h5.data().empty());

    string a = "1 1 1 1 2 3 3 44 4 44 4 43 3 2 1";
    Histogram ht1(a);

    string b = "1 1 1 3 44 3 43";
    Histogram ht2(b);

    Histogram ht3 = ht1 - ht2;

    ASSERT_FALSE(ht1 == ht2 || ht1 == ht3);
}
