#include <gtest/gtest.h>
#include "../lexer.h"
#include "../data.h"
#include "../places.h"
#include "../token.h"
#include <iostream>
using namespace std;

TEST(WWW, TEST1){
    istringstream isl("2020-05-15T09:00:00 02 40 90\n"
                      "2020-05-15T06:08:00 01 40 10\n"
                      "2020-05-15T04:00:00 02 10 35\n"
                      "2020-05-15T11:00:00 01 00 00\n"
                      "2020-05-15T12:00:00 03 90 20\n"
                      "2020-05-15T09:00:20 01 60 30\n"
                      "2020-05-15T09:05:00 01 80 20\n"
                      "2020-05-15T09:20:00 01 10 70\n"
                      "2020-05-15T09:03:44 03 100 200");

    istringstream isp("Lenin_Square 30 00 80 20\n"
                      "Theatre      50 15 60 05\n"
                      "Central_Park 80 60 55 25\n"
                      "Barbershop   00 30 20 40\n"
                      "Metro        10 70 10 70\n"
                      "Shop_Area    15 70 90 99\n"
                      "Gallery      25 86 45 95\n"
                      "Home         00 00 10 10");

    Lexer l;
    l.init_tokens(isl);

    Data d(l);

    Places pl;
    pl.init_places(isp);

    string user1_path = "User id: 1 path:\n"
                        "Home->Metro->Lenin_Square->Central_Park->Lenin_Square->Finish";

    string user2_path = "User id: 2 path:\n"
                        "Shop_Area->Barbershop->Finish";

    string user3_path = "User id: 3 path:\n"
                        "[Unknown Place]->[Unknown Place]->Finish";

    EXPECT_EQ(user1_path, d.user_path(1, pl));
    EXPECT_EQ(user2_path, d.user_path(2, pl));
    EXPECT_EQ(user3_path, d.user_path(3, pl));
}