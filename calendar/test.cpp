#include <gtest/gtest.h>
#include <iostream>
#include "../run.h"
#include "../calendar.h"

using namespace std;

TEST(CalendarInput, FromCLI) {
    struct TestInputs {
        bool valid{};
        const char* input{};
    };
    const TestInputs inputs[] = {
            {true, "range 1 1990 2 1991 | vert year_once"},
            {true, "year 1991 | vert year_for_every_month"},
            {false, "yyear 1991 | vert year_for_every_month"},
            {false, ""},
            {false, "werqdnfkjacgrieacg | q jkjlrgncqklgqecg"},
            {false, "month 12 1001 | vert year_once"},
            {false, "year -1 | horiz year_for_every_month"},
            {false, "range 12 1991 1 1991 | vert year_once"},
            {true, "month 1991 12 | horiz year_once"},
            {false, "month 1991 12 | horiz year_once something else"},
            {false, "year 1234 | vert horiz"},
            {false, "month 1991 12 | year_once horiz"}

    };
    for (auto& input: inputs) {
        std::istringstream is(input.input);
        auto args = parsefile(is);
        EXPECT_NE(args.flag_error, input.valid) << "Error parsing input:'" << input.input << "' must be " << (input.valid?"valid":"invalid") << std::endl;
    }
}

TEST(CalendarOutputYear, ToCLI){
    std::istringstream is("year 1991 | vert year_for_every_month");
    auto arguments = parsefile(is);
    int orient = arguments.horiz ? 0 : 1;
    std:: string year_1991 = print_date(arguments.month1, arguments.year1, arguments.month2, arguments.year2,
                                   arguments.year_for_every_month, arguments.year_once, orient);

    std::string real_year_1991 = {"   January 1991       February 1991       March 1991         April 1991     \n"
                                  "Mn     7 14 21 28         4 11 18 25         4 11 18 25      1  8 15 22 29   \n"
                                  "Tu  1  8 15 22 29         5 12 19 26         5 12 19 26      2  9 16 23 30   \n"
                                  "Wd  2  9 16 23 30         6 13 20 27         6 13 20 27      3 10 17 24      \n"
                                  "Th  3 10 17 24 31         7 14 21 28         7 14 21 28      4 11 18 25      \n"
                                  "Fr  4 11 18 25         1  8 15 22         1  8 15 22 29      5 12 19 26      \n"
                                  "St  5 12 19 26         2  9 16 23         2  9 16 23 30      6 13 20 27      \n"
                                  "Sn  6 13 20 27         3 10 17 24         3 10 17 24 31      7 14 21 28      \n"
                                  "     May 1991           June 1991          July 1991         August 1991    \n"
                                  "Mn     6 13 20 27         3 10 17 24      1  8 15 22 29         5 12 19 26   \n"
                                  "Tu     7 14 21 28         4 11 18 25      2  9 16 23 30         6 13 20 27   \n"
                                  "Wd  1  8 15 22 29         5 12 19 26      3 10 17 24 31         7 14 21 28   \n"
                                  "Th  2  9 16 23 30         6 13 20 27      4 11 18 25         1  8 15 22 29   \n"
                                  "Fr  3 10 17 24 31         7 14 21 28      5 12 19 26         2  9 16 23 30   \n"
                                  "St  4 11 18 25         1  8 15 22 29      6 13 20 27         3 10 17 24 31   \n"
                                  "Sn  5 12 19 26         2  9 16 23 30      7 14 21 28         4 11 18 25      \n"
                                  "  September 1991      October 1991       November 1991      December 1991   \n"
                                  "Mn     2  9 16 23 30      7 14 21 28         4 11 18 25         2  9 16 23 30\n"
                                  "Tu     3 10 17 24      1  8 15 22 29         5 12 19 26         3 10 17 24 31\n"
                                  "Wd     4 11 18 25      2  9 16 23 30         6 13 20 27         4 11 18 25   \n"
                                  "Th     5 12 19 26      3 10 17 24 31         7 14 21 28         5 12 19 26   \n"
                                  "Fr     6 13 20 27      4 11 18 25         1  8 15 22 29         6 13 20 27   \n"
                                  "St     7 14 21 28      5 12 19 26         2  9 16 23 30         7 14 21 28   \n"
                                  "Sn  1  8 15 22 29      6 13 20 27         3 10 17 24         1  8 15 22 29   \n"};

    EXPECT_EQ(year_1991, real_year_1991);
}

TEST(CalendarOutputMonth, ToCLI){
    std::istringstream is("month 1991 12 | horiz year_for_every_month");
    auto arguments = parsefile(is);
    int orient = arguments.horiz ? 0 : 1;
    std:: string december_1991 = print_date(arguments.month1, arguments.year1, arguments.month2, arguments.year2,
                                        arguments.year_for_every_month, arguments.year_once, orient);

    std::string real_december_1991 = {"    December 1991     \n"
                                      "Mn Tu Wd Th Fr St Sn\n"
                                      "                   1\n"
                                      " 2  3  4  5  6  7  8\n"
                                      " 9 10 11 12 13 14 15\n"
                                      "16 17 18 19 20 21 22\n"
                                      "23 24 25 26 27 28 29\n"
                                      "30 31                  "};

    EXPECT_EQ(december_1991, real_december_1991);
}

TEST(CalendarOutputRange1, ToCLI){
    std::istringstream is("range 1 1991 5 1991 | horiz year_for_every_month");
    auto arguments = parsefile(is);
    int orient = arguments.horiz ? 0 : 1;
    std:: string range = print_date(arguments.month1, arguments.year1, arguments.month2, arguments.year2,
                                            arguments.year_for_every_month, arguments.year_once, orient);

    std::string real_range = {"     January 1991         February 1991           March 1991            April 1991      \n"
                              "Mn Tu Wd Th Fr St Sn  Mn Tu Wd Th Fr St Sn  Mn Tu Wd Th Fr St Sn  Mn Tu Wd Th Fr St Sn\n"
                              "    1  2  3  4  5  6               1  2  3               1  2  3   1  2  3  4  5  6  7\n"
                              " 7  8  9 10 11 12 13   4  5  6  7  8  9 10   4  5  6  7  8  9 10   8  9 10 11 12 13 14\n"
                              "14 15 16 17 18 19 20  11 12 13 14 15 16 17  11 12 13 14 15 16 17  15 16 17 18 19 20 21\n"
                              "21 22 23 24 25 26 27  18 19 20 21 22 23 24  18 19 20 21 22 23 24  22 23 24 25 26 27 28\n"
                              "28 29 30 31           25 26 27 28           25 26 27 28 29 30 31  29 30               \n"
                              "       May 1991       \n"
                              "Mn Tu Wd Th Fr St Sn\n"
                              "       1  2  3  4  5\n"
                              " 6  7  8  9 10 11 12\n"
                              "13 14 15 16 17 18 19\n"
                              "20 21 22 23 24 25 26\n"
                              "27 28 29 30 31      "};

    EXPECT_EQ(range, real_range);
}

TEST(CalendarOutputRange2, ToCLI){
    std::istringstream is("range 1 1991 5 1992 | vert year_once");
    auto arguments = parsefile(is);
    int orient = arguments.horiz ? 0 : 1;
    std:: string range = print_date(arguments.month1, arguments.year1, arguments.month2, arguments.year2,
                                    arguments.year_for_every_month, arguments.year_once, orient);

    std::string real_range = {"                                   1991                                    \n"
                              "      January           February             March              April       \n"
                              "Mn     7 14 21 28         4 11 18 25         4 11 18 25      1  8 15 22 29   \n"
                              "Tu  1  8 15 22 29         5 12 19 26         5 12 19 26      2  9 16 23 30   \n"
                              "Wd  2  9 16 23 30         6 13 20 27         6 13 20 27      3 10 17 24      \n"
                              "Th  3 10 17 24 31         7 14 21 28         7 14 21 28      4 11 18 25      \n"
                              "Fr  4 11 18 25         1  8 15 22         1  8 15 22 29      5 12 19 26      \n"
                              "St  5 12 19 26         2  9 16 23         2  9 16 23 30      6 13 20 27      \n"
                              "Sn  6 13 20 27         3 10 17 24         3 10 17 24 31      7 14 21 28      \n"
                              "        May               June               July              August       \n"
                              "Mn     6 13 20 27         3 10 17 24      1  8 15 22 29         5 12 19 26   \n"
                              "Tu     7 14 21 28         4 11 18 25      2  9 16 23 30         6 13 20 27   \n"
                              "Wd  1  8 15 22 29         5 12 19 26      3 10 17 24 31         7 14 21 28   \n"
                              "Th  2  9 16 23 30         6 13 20 27      4 11 18 25         1  8 15 22 29   \n"
                              "Fr  3 10 17 24 31         7 14 21 28      5 12 19 26         2  9 16 23 30   \n"
                              "St  4 11 18 25         1  8 15 22 29      6 13 20 27         3 10 17 24 31   \n"
                              "Sn  5 12 19 26         2  9 16 23 30      7 14 21 28         4 11 18 25      \n"
                              "     September           October           November           December      \n"
                              "Mn     2  9 16 23 30      7 14 21 28         4 11 18 25         2  9 16 23 30\n"
                              "Tu     3 10 17 24      1  8 15 22 29         5 12 19 26         3 10 17 24 31\n"
                              "Wd     4 11 18 25      2  9 16 23 30         6 13 20 27         4 11 18 25   \n"
                              "Th     5 12 19 26      3 10 17 24 31         7 14 21 28         5 12 19 26   \n"
                              "Fr     6 13 20 27      4 11 18 25         1  8 15 22 29         6 13 20 27   \n"
                              "St     7 14 21 28      5 12 19 26         2  9 16 23 30         7 14 21 28   \n"
                              "Sn  1  8 15 22 29      6 13 20 27         3 10 17 24         1  8 15 22 29   \n"
                              "\n"
                              "                                   1992                                    \n"
                              "      January           February             March              April       \n"
                              "Mn     6 13 20 27         3 10 17 24         2  9 16 23 30      6 13 20 27   \n"
                              "Tu     7 14 21 28         4 11 18 25         3 10 17 24 31      7 14 21 28   \n"
                              "Wd  1  8 15 22 29         5 12 19 26         4 11 18 25      1  8 15 22 29   \n"
                              "Th  2  9 16 23 30         6 13 20 27         5 12 19 26      2  9 16 23 30   \n"
                              "Fr  3 10 17 24 31         7 14 21 28         6 13 20 27      3 10 17 24      \n"
                              "St  4 11 18 25         1  8 15 22 29         7 14 21 28      4 11 18 25      \n"
                              "Sn  5 12 19 26         2  9 16 23         1  8 15 22 29      5 12 19 26      \n"
                              "        May        \n"
                              "Mn     4 11 18 25   \n"
                              "Tu     5 12 19 26   \n"
                              "Wd     6 13 20 27   \n"
                              "Th     7 14 21 28   \n"
                              "Fr  1  8 15 22 29   \n"
                              "St  2  9 16 23 30   \n"
                              "Sn  3 10 17 24 31   \n"
                              ""};

    EXPECT_EQ(range, real_range);
}

TEST(CalendarOutputLeapMonth, ToCLI){
    std::istringstream is("month 2020 2 | horiz year_for_every_month");
    auto arguments = parsefile(is);
    int orient = arguments.horiz ? 0 : 1;
    std:: string leap_month = print_date(arguments.month1, arguments.year1, arguments.month2, arguments.year2,
                                            arguments.year_for_every_month, arguments.year_once, orient);

    std::string real_leap_month =   {"    February 2020     \n"
                                      "Mn Tu Wd Th Fr St Sn\n"
                                      "                1  2\n"
                                      " 3  4  5  6  7  8  9\n"
                                      "10 11 12 13 14 15 16\n"
                                      "17 18 19 20 21 22 23\n"
                                      "24 25 26 27 28 29   "};

    EXPECT_EQ(leap_month, real_leap_month);
}