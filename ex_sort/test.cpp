#include <gtest/gtest.h>
#include "../external_sort.h"
#include <ctime>
#include <cstdlib>
#include <vector>
#include <fstream>

#define N 100
using namespace std;

TEST(Constructors, BadConstructorTest){
   EXPECT_NO_THROW(ExternalMergeSort("", "", 0));
}

TEST(Constructors, GoodConstructorTest){
    EXPECT_NO_THROW(ExternalMergeSort("1.txt", "2.txt", 1));
}

TEST(Sorting, ChunksBiggerSize){
    std :: vector<int> vivi;
    std :: ofstream hot_loads("ex_test.txt");
    for(int j = 0; j < 10; j ++) {
        srand(time(NULL));
        int temp = rand();
        vivi.push_back(temp);
        hot_loads << temp << " ";
    }
    hot_loads.close();

    std :: sort(vivi.begin(), vivi.end());
    ExternalMergeSort m("ex_test.txt", "sort_ex_test.txt", 4);
    m.MergeSort();
    std :: fstream loads("sort_ex_test.txt");
    std :: vector<int> init_vivi;
    std :: string num;
    while (loads >> num){
        init_vivi.push_back(stoi(num));
    }
    for(int i = 0; i < vivi.size(); i ++)
        EXPECT_EQ(vivi[i], init_vivi[i]);
}

TEST(Sorting, ChunkEqualSize){
    std :: vector<int> vivi;
    std :: ofstream hot_loads("ex_test.txt");
    for(int j = 0; j < 10; j ++) {
        srand(time(NULL));
        int temp = rand();
        vivi.push_back(temp);
        hot_loads << temp << " ";
    }
    hot_loads.close();

    std :: sort(vivi.begin(), vivi.end());
    ExternalMergeSort m("ex_test.txt", "sort_ex_test.txt", 10);
    m.MergeSort();
    std :: fstream loads("sort_ex_test.txt");
    std :: vector<int> init_vivi;
    std :: string num;
    while (loads >> num){
        init_vivi.push_back(stoi(num));
    }
    for(int i = 0; i < vivi.size(); i ++)
        EXPECT_EQ(vivi[i], init_vivi[i]);
}

TEST(Sorting, ChunkEBiggerSize){
    std :: vector<int> vivi;
    std :: ofstream hot_loads("ex_test.txt");
    for(int j = 0; j < 10; j ++) {
        srand(time(NULL));
        int temp = rand();
        vivi.push_back(temp);
        hot_loads << temp << " ";
    }
    hot_loads.close();

    std :: sort(vivi.begin(), vivi.end());
    ExternalMergeSort m("ex_test.txt", "sort_ex_test.txt", 15);
    m.MergeSort();
    std :: fstream loads("sort_ex_test.txt");
    std :: vector<int> init_vivi;
    std :: string num;
    while (loads >> num){
        init_vivi.push_back(stoi(num));
    }
    for(int i = 0; i < vivi.size(); i ++)
        EXPECT_EQ(vivi[i], init_vivi[i]);
}