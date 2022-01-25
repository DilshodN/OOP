#include "calendar.h"

// сделать namespace
// append -> +=  ++
// template без stream
// year тоеж
// get_n_week через get_line
// try vector in print_n_months
// pop_back на erase('\n')

namespace {
    const std::string days = "Mn Tu Wd Th Fr St Sn";

    int dayNumber(int day, int month, int year) {
        const static int t[] = {0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4};
        year -= month < 3;
        return (year + year / 4 - year / 100 + year / 400 + t[month - 1] + day - 1) % 7;
    }

    std::string getMonthName(int monthNumber) {
        const static std::string months[] = {"January", "February", "March",
                                             "April", "May", "June",
                                             "July", "August", "September",
                                             "October", "November", "December"
        };
        return (months[monthNumber]);
    }

    int numberOfDays(int monthNumber, int year) {
        switch (monthNumber) {
            case 0 :
            case 2 :
            case 4 :
            case 6 :
            case 7 :
            case 9 :
            case 11:
                return (31);
            case 1 :
                if (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0))
                    return (29);
                else
                    return (28);

            case 3 :
            case 5 :
            case 8 :
            case 10 :
                return (30);
            default:
                return -1;
        }
    }

    void fill(std::string &str, size_t n) {
        if (n == 0) return;
        str += std::string(n, ' ');
    }

    std::string set_in_middle(const std::string &str, size_t width) {
        std::string temp;
        size_t mid = (width - str.length()) / 2;
        fill(temp, mid);
        temp += str;
        fill(temp, width - temp.length());
        return temp;
    }

    std::string repeat_str(const std::string &str, int n, const char *fillchar) {
        std::string temp;
        std::string tempfill = fillchar;
        for (int i = 0; i < n - 1; i++) temp += str + fillchar;
        temp += str;
        return temp;
    }

    std::string template_of_n_horiz_month(int month, int year, bool with_year, bool every_year, int n) {
        std::string out;
        std::string weeks = repeat_str(days, n, "  ");
        if (with_year) out += set_in_middle(std::to_string(year), 4 * days.length()) + '\n';

        for (int i = 0; i < n; i++) {
            std::string month_with_year = getMonthName(month + i);
            if (every_year) {
                month_with_year += " " + std::to_string(year);
            }
            out += set_in_middle(month_with_year, days.length() + 2);
        }
        out += '\n' + weeks;
        return out;
    }

    int how_many_weeks(int month, int year) {
        int count = 0;
        int current = dayNumber(1, month + 1, year);
        int days_in_month = numberOfDays(month, year);
        int k = current - 1;
        for (int i = 1; i <= days_in_month; i++)
            if (++k > 6) {
                k = 0;
                count++;
            }
        return count + 1;
    }

    std::string horiz_month(int month, int year) {
        std::ostringstream out;

        int current = dayNumber(1, month + 1, year);
        int days_in_month = numberOfDays(month, year);
        int k = current;
        out << std::string(current * 3, ' ');
        for (int i = 1; i <= days_in_month; i++) {
            out << std::right << std::setw(2) << i << " ";
            if (++k > 6) {
                k = 0;
                out << std::endl;
            }
        }
        std::string final = out.str();
        final.pop_back(); // delete /n

        int current_of_next = dayNumber(1, month + 2, year);
        int how_many_tabs = 6 - current_of_next;
        if (current_of_next != 0) fill(final, (how_many_tabs + 1) * 3);

        else if (month != 11) final.pop_back();

        return final;
    }

// ??
    std::string get_n_week(int month, int year, int n) {
        if (n > how_many_weeks(month, year)) {
            return std::string(20, ' ');
        }

        std::string month_data = horiz_month(month, year);
        std::string temp;
        int counter = 0;
        for (auto elem: month_data) {
            if (elem == '\n') {
                counter++;
                if (counter == n)
                    break;
                temp.clear();
                continue;
            }

            temp += elem;
        }
        if (n != how_many_weeks(month, year)) temp.pop_back();
        return temp;
    }


    std::string print_n_horiz_month(int month, int n, int year, bool flag_year, bool every_year) {
        std::string out;
        out += template_of_n_horiz_month(month, year, flag_year, every_year, n) + '\n';
        std::vector<int> v;

        for (int i = 0; i < n; i++) v.push_back(how_many_weeks(month + i, year));

        long int max_len_week = v[std::distance(v.begin(), std::max_element(v.begin(), v.end()))];


        for (int j = 1; j <= max_len_week; j++) {
            for (int k = 0; k < n - 1; k++) {
                out += get_n_week(month + k, year, j) + "  ";
            }
            out += get_n_week(month + n - 1, year, j) + '\n';
        }

        out.pop_back();
        return out;
    }


    std::string horiz_year_in_range(int month1, int year1, int month2, int year2, bool every_year, bool year_once) {
        std::ostringstream out;
        bool flag_year = year_once;
        if (month1 == month2 && year1 == year2) {
            out << print_n_horiz_month(month1 - 1, 1, year1, flag_year, every_year);
        } else if (month1 < month2 && year1 == year2) {
            int how_many_month = month2 - month1 + 1;

            if (how_many_month < 4) {
                int year = year1;
                out << print_n_horiz_month(month1 - 1, how_many_month, year, flag_year, every_year) << std::endl;
            } else if ((how_many_month) % 4 == 0) {
                int year = year1;
                int k = how_many_month / 4;
                for (int i = 0; i < k; i ++) {
                    out << print_n_horiz_month(month1 + 4 * i - 1, 4, year, flag_year, every_year) << std::endl;
                    flag_year = false;
                }
            } else if (how_many_month == 5 || how_many_month == 6 || how_many_month == 7) {
                int year = year1;
                out << print_n_horiz_month(month1 - 1, 4, year, flag_year, every_year) << std::endl;
                flag_year = false;
                out << print_n_horiz_month(month1 + 3, how_many_month - 4, year, flag_year, every_year);
            } else if (how_many_month == 9 || how_many_month == 10 || how_many_month == 11) {
                int year = year1;
                out << print_n_horiz_month(month1 - 1, 4, year, flag_year, every_year) << std::endl;
                flag_year = false;
                out << print_n_horiz_month(month1 + 3, 4, year, flag_year, every_year) << std::endl;

                out << print_n_horiz_month(month1 + 3 + 4, how_many_month - 4 - 4, year, flag_year, every_year);

            }

        } else if (year1 < year2) {
            int k = year2 - year1 - 1;

            std::string part1 = horiz_year_in_range(month1, year1, 12, year1, every_year, flag_year);
            out << part1 << std::endl;

            if (k >= 1) {
                for (int i = year1 + 1; i < year2; i++)
                    out << horiz_year_in_range(1, i, 12, i, every_year, flag_year) << std::endl;
            }

            std::string part2 = horiz_year_in_range(1, year2, month2, year2, every_year, flag_year);
            out << part2 << std::endl;

        }

        return out.str();
    }

    std::string horiz_year(int year, bool every_year, bool flag_year) {
        return horiz_year_in_range(0, year, 11, year, every_year, flag_year);
    }

    std::string vert_month(int month, int year) {
        std::ostringstream out;

        int days_in_month = numberOfDays(month, year);

        std::vector<std::vector<int>> days_of_week(7);

        for (int i = 1; i <= days_in_month; i++) {
            int current = dayNumber(i, month + 1, year);
            days_of_week[current].push_back(i);
        }

        bool was_first_day = false;
        for (auto &day_of_week: days_of_week) {
            if (!was_first_day) {
                bool first_day = day_of_week[0] == 1;
                if (!first_day) out << "   ";
                if (first_day) was_first_day = true;
            }

            for (int day: day_of_week) {
                out << std::right << std::setw(2) << day << " ";
            }
            out << std::endl;
        }
        std::string final = out.str();
        final.pop_back(); // delete "\n"

        return final;
    }

    std::string template_of_n_vert_month(int month, int year, bool with_year, bool every_year, int n) {
        std::string out;
        std::string months;
        for (int i = 0; i < n; i++) {
            std::string month_name = getMonthName(month + i);
            if (every_year) {
                month_name += " " + std::to_string(year);
            }
            months += set_in_middle(month_name, 19);
        }
        if (with_year) out += set_in_middle(std::to_string(year), 75) + '\n';
        out += months;
        return out;
    }

    std::string get_n_day_of_week(int month, int year, int n) {
        std::string month_data = vert_month(month, year);
        std::string temp;
        int counter = 0;
        for (auto elem: month_data) {
            if (elem == '\n') {
                counter++;
                if (counter == n)
                    break;
                temp.clear();
                continue;
            }
            temp += elem;
        }
        temp.pop_back();

        if (temp.length() >= 16) // минимальная длина строки в vert положении
            return temp;
        fill(temp, 17 - temp.length());
        return temp;

    }

    std::string day_name(int n) {
        const static std::string days_of_week[] = {"Mn", "Tu", "Wd", "Th", "Fr", "St", "Sn"};
        return (days_of_week[n]);
    }

    std::string print_n_vert_month(int month, int n, int year, bool flag_year, bool every_year) {

        std::string out;
        out += template_of_n_vert_month(month, year, flag_year, every_year, n) + '\n';

        for (int j = 1; j <= 7; j++) {
            out += day_name(j - 1) + " ";
            for (int k = 0; k < n - 1; k++)
                out += get_n_day_of_week(month + k, year, j) + "  ";

            out += get_n_day_of_week(month + n - 1, year, j) + '\n';
        }

        out.pop_back();
        return out;
    }

    std::string vert_year_in_range(int month1, int year1, int month2, int year2, bool every_year, bool year_once) {
        std::ostringstream out;
        bool flag_year = year_once;
        if (month1 == month2 && year1 == year2) {
            out << print_n_vert_month(month1 - 1, 1, year1, flag_year, every_year);
        } else if (month1 < month2 && year1 == year2) {
            int how_many_month = month2 - month1 + 1;

            if (how_many_month < 4) {
                int year = year1;
                out << print_n_vert_month(month1 - 1, how_many_month, year, flag_year, every_year) << std::endl;
            } else if ((how_many_month) % 4 == 0) {
                int year = year1;
                int k = how_many_month / 4;
                for (int i = 0; i < k; i ++) {
                    out << print_n_vert_month(month1 + 4 * i - 1, 4, year, flag_year, every_year) << std::endl;
                    flag_year = false;
                }
            } else if (how_many_month == 5 || how_many_month == 6 || how_many_month == 7) {
                int year = year1;
                out << print_n_vert_month(month1 - 1, 4, year, flag_year, every_year) << std::endl;
                flag_year = false;
                out << print_n_vert_month(month1 + 3, how_many_month - 4, year, flag_year, every_year);
            } else if (how_many_month == 9 || how_many_month == 10 || how_many_month == 11) {
                int year = year1;
                out << print_n_vert_month(month1 - 1, 4, year, flag_year, every_year) << std::endl;
                flag_year = false;
                out << print_n_vert_month(month1 + 3, 4, year, flag_year, every_year) << std::endl;

                out << print_n_vert_month(month1 + 3 + 4, how_many_month - 4 - 4, year, flag_year, every_year);

            }

        } else if (year1 < year2) {
            int k = year2 - year1 - 1;

            std::string part1 = vert_year_in_range(month1, year1, 12, year1, every_year, flag_year);
            out << part1 << std::endl;

            if (k >= 1) {
                for (int i = year1 + 1; i < year2; i++)
                    out << vert_year_in_range(1, i, 12, i, every_year, flag_year) << std::endl;
            }

            std::string part2 = vert_year_in_range(1, year2, month2, year2, every_year, flag_year);
            out << part2 << std::endl;

        }

        return out.str();
    }


    std::string vert_year(int year, bool every_year, bool flag_year) {
        return vert_year_in_range(0, year, 11, year, every_year, flag_year);
    }
}



std::string print_date(int month1, int year1, int month2, int year2, bool with_years, bool flag_year, int orient){
    // 0 - horiz
    // 1 - vert
    switch(orient){
        case 0:
            return horiz_year_in_range(month1, year1, month2, year2, with_years, flag_year);
        case 1:
            return vert_year_in_range(month1, year1, month2, year2, with_years, flag_year);
        default:
            return "";
    }
}