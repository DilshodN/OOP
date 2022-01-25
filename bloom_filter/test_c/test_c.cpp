#include <gtest/gtest.h>
extern "C" {
#include "../refac.h"
}

unsigned int string_hash(void *string)
{
    unsigned int result = 5381;
    unsigned char *p;

    p = (unsigned char *) string;

    while (*p != '\0') {
        result = (result << 5) + result + *p;
        ++p;
    }
    return result;
}

TEST(BloomFilterC, NewFree){
    BloomFilter* filter;
    filter = bloom_filter_new(128, string_hash, 1);

    ASSERT_TRUE(filter != nullptr);
    bloom_filter_free(filter);
    filter = bloom_filter_new(128, string_hash, 64);
    ASSERT_TRUE(filter != nullptr);

    bloom_filter_free(filter);
    filter = bloom_filter_new(128, string_hash, 50000);
    ASSERT_TRUE(filter == nullptr);
}

TEST(BloomFilterC, InsertQuery){
    BloomFilter *filter;


    filter = bloom_filter_new(128, string_hash, 4);


    EXPECT_EQ(bloom_filter_query(filter, (BloomFilterValue) "test 1"), 0);
    EXPECT_EQ(bloom_filter_query(filter, (BloomFilterValue)"test 2"), 0);


    bloom_filter_insert(filter, (BloomFilterValue)"test 1");
    bloom_filter_insert(filter, (BloomFilterValue)"test 2");


    EXPECT_NE(bloom_filter_query(filter, (BloomFilterValue)"test 1"), 0);
    EXPECT_NE(bloom_filter_query(filter, (BloomFilterValue)"test 2"), 0);

    bloom_filter_free(filter);
}

TEST(BloomFilterC, ReadLoad){
    BloomFilter *filter1;
    BloomFilter *filter2;
    unsigned char state[16];


    filter1 = bloom_filter_new(128, string_hash, 4);

    bloom_filter_insert(filter1, (BloomFilterValue)"test 1");
    bloom_filter_insert(filter1, (BloomFilterValue)"test 2");


    bloom_filter_read(filter1, state);

    bloom_filter_free(filter1);


    filter2 = bloom_filter_new(128, string_hash, 4);

    bloom_filter_load(filter2, state);


    EXPECT_NE(bloom_filter_query(filter2, (BloomFilterValue)"test 1"), 0);
    EXPECT_NE(bloom_filter_query(filter2, (BloomFilterValue)"test 2"), 0);

    bloom_filter_free(filter2);
}

TEST(BloomFilterC, Intersection)
{
    BloomFilter *filter1;
    BloomFilter *filter2;
    BloomFilter *result;


    filter1 = bloom_filter_new(128, string_hash, 4);

    bloom_filter_insert(filter1, (BloomFilterValue)"test 1");
    bloom_filter_insert(filter1, (BloomFilterValue)"test 2");


    filter2 = bloom_filter_new(128, string_hash, 4);

    bloom_filter_insert(filter2, (BloomFilterValue)"test 1");

    EXPECT_EQ(bloom_filter_query(filter2, (BloomFilterValue)"test 2"), 0);

    result = bloom_filter_intersection(filter1, filter2);


    EXPECT_NE(bloom_filter_query(result, (BloomFilterValue)"test 1"), 0);
    assert(bloom_filter_query(result, (BloomFilterValue)"test 2") == 0);

    bloom_filter_free(result);
    bloom_filter_free(filter1);
    bloom_filter_free(filter2);
}

TEST(BloomFilterC, Union)
{
    BloomFilter *filter1;
    BloomFilter *filter2;
    BloomFilter *result;


    filter1 = bloom_filter_new(128, string_hash, 4);

    bloom_filter_insert(filter1, (BloomFilterValue)"test 1");

    filter2 = bloom_filter_new(128, string_hash, 4);

    bloom_filter_insert(filter2, (BloomFilterValue)"test 2");

    result = bloom_filter_union(filter1, filter2);


    EXPECT_NE(bloom_filter_query(result, (BloomFilterValue)"test 1"), 0);
    EXPECT_NE(bloom_filter_query(result, (BloomFilterValue)"test 2"), 0);

    bloom_filter_free(result);
    bloom_filter_free(filter1);
    bloom_filter_free(filter2);
}