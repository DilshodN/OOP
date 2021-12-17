#include <gtest/gtest.h>
#include "../bloom_filter.h"

uint64_t c_hash(uint64_t x) {
    x = (x ^ (x >> 30)) * UINT64_C(0xbf58476d1ce4e5b9);
    x = (x ^ (x >> 27)) * UINT64_C(0x94d049bb133111eb);
    x = x ^ (x >> 31);
    return x;
}

BloomFilter<int, std::hash<int>, 3, 4> bf;
BloomFilter<double> basic_bf;

TEST(BloomFilterCpp, TableSize){
    EXPECT_EQ(bf.table_size(), 3);
    EXPECT_EQ(basic_bf.table_size(), 50);
}

TEST(BloomFilterCpp, NumOfFunctions){
    EXPECT_EQ(bf.num_of_functions(), 4);
    EXPECT_EQ(basic_bf.num_of_functions(), 64);
}

TEST(BloomFilterCpp, Table){
    EXPECT_EQ(bf.read(), std::bitset<3>{});
    EXPECT_EQ(basic_bf.read(), std::bitset<50>{});
}

TEST(BloomFilterCpp, InsertQueryTestDouble){
    BloomFilter<double> double_bf;

    EXPECT_FALSE(double_bf.query(34.2));
    EXPECT_FALSE(double_bf.query(34.3));
    EXPECT_FALSE(double_bf.query(1));

    double_bf.insert(34.2);
    EXPECT_TRUE(double_bf.query(34.2));
    EXPECT_FALSE(double_bf.query(34.3));
    EXPECT_FALSE(double_bf.query(1));

    double_bf.insert(34.3);
    EXPECT_TRUE(double_bf.query(34.2));
    EXPECT_TRUE(double_bf.query(34.3));
    EXPECT_FALSE(double_bf.query(1));

    double_bf.insert(1);
    EXPECT_TRUE(double_bf.query(34.2));
    EXPECT_TRUE(double_bf.query(34.3));
    EXPECT_TRUE(double_bf.query(1));
}

TEST(BloomFilterCpp, InsertQueryTestString){
    BloomFilter<std::string> string_bf;

    EXPECT_FALSE(string_bf.query("a"));
    EXPECT_FALSE(string_bf.query("b"));
    EXPECT_FALSE(string_bf.query("c"));

    string_bf.insert("a");
    EXPECT_TRUE(string_bf.query("a"));
    EXPECT_FALSE(string_bf.query("b"));
    EXPECT_FALSE(string_bf.query("c"));

    string_bf.insert("b");
    EXPECT_TRUE(string_bf.query("a"));
    EXPECT_TRUE(string_bf.query("b"));
    EXPECT_FALSE(string_bf.query("c"));

    string_bf.insert("c");
    EXPECT_TRUE(string_bf.query("a"));
    EXPECT_TRUE(string_bf.query("b"));
    EXPECT_TRUE(string_bf.query("c"));
}


TEST(BloomFilterCpp, InsertQueryTestInt){
    BloomFilter<int> int_bf;

    EXPECT_FALSE(int_bf.query(1));
    EXPECT_FALSE(int_bf.query(2));
    EXPECT_FALSE(int_bf.query(3));

    int_bf.insert(1);
    EXPECT_TRUE(int_bf.query(1));
    EXPECT_FALSE(int_bf.query(2));
    EXPECT_FALSE(int_bf.query(3));

    int_bf.insert(2);
    EXPECT_TRUE(int_bf.query(1));
    EXPECT_TRUE(int_bf.query(2));
    EXPECT_FALSE(int_bf.query(3));

    int_bf.insert(3);
    EXPECT_TRUE(int_bf.query(1));
    EXPECT_TRUE(int_bf.query(2));
    EXPECT_TRUE(int_bf.query(3));
}

TEST(BloomFilterCpp, LoadRead){
    EXPECT_EQ(bf.read(), std::bitset<3>{});
    EXPECT_EQ(basic_bf.read(), std::bitset<50>{});

    BloomFilter<int> int_bf;
    EXPECT_EQ(int_bf.read(), std::bitset<50>{});
    auto read_bitset = int_bf.read();
    read_bitset.set();
    int_bf.load(read_bitset);
    EXPECT_FALSE(int_bf.read() == std::bitset<50>{});
    EXPECT_EQ(int_bf.read(), std::bitset<50>{}.set());
    for(int i = 0; i < 1000; i++){
        ASSERT_TRUE(int_bf.query(i));
    }
}

TEST(BloomFilterCpp, Union){
    BloomFilter<int, std::hash<int>, 3, 3> int_bf1;
    BloomFilter<int, std::hash<int>, 3, 3> int_bf2;
    auto empty_union = int_bf1 | int_bf2;
    EXPECT_EQ(int_bf1.read(), std::bitset<3>{});
    EXPECT_EQ(int_bf2.read(), std::bitset<3>{});
    EXPECT_EQ(empty_union.read(), std::bitset<3>{});

    int_bf1.insert(1);
    int_bf2.insert(2);
    auto non_empty_union = int_bf1 | int_bf2;
    EXPECT_EQ(non_empty_union.read(), std::bitset<3>{}.set());
}

TEST(BloomFilterCpp, Intersection){
    BloomFilter<int, std::hash<int>, 3, 3> int_bf1;
    BloomFilter<int, std::hash<int>, 3, 3> int_bf2;
    auto empty_intersection = int_bf1 & int_bf2;
    EXPECT_EQ(int_bf1.read(), std::bitset<3>{});
    EXPECT_EQ(int_bf2.read(), std::bitset<3>{});
    EXPECT_EQ(empty_intersection.read(), std::bitset<3>{});

    int_bf1.insert(1);
    int_bf2.insert(2);
    auto non_empty_intersection = int_bf1 & int_bf2;
    EXPECT_EQ(non_empty_intersection.read(), std::bitset<3>{}.set(2));
}
