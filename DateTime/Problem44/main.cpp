#include <gsl/gsl>
#include <iomanip>
#include <iostream>

constexpr int start_day_of_week(int year, int month) {
    int front = year / 100;
    int back = year % 100;
    int h = ((1 + (month + 1) * 13 / 5 + back + back / 4 + front / 4 - 2 * front) % 7 + 6) % 7;
    return h;
}

constexpr int n_day_in_month(int year, int month) {
    constexpr int n_day[] = { -1, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    auto n_day_in_year = [](int year) constexpr {
        if (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0)) 
            return 366;
        else 
            return 365;
    };

    if (month == 2 && n_day_in_year(year) == 366) {
        return 29;
    }
    return n_day[month];
}

int main() {
    int y, m;
    std::cin >> y >> m;

    int w = start_day_of_week(y, m);
    const char* week[] = { "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };

    for (auto s : week) {
        std::cout << s << ' ';
    }
    std::cout << '\n';

    int iter = 0;
    for (; iter < w; ++iter) {
        std::cout << "    ";
    }

    for (int i = 1; i <= n_day_in_month(y, m); ++i, ++iter) {
        std::cout << std::setw(3) << i << ' ';
        if (iter % 7 == 6) {
            std::cout << '\n';
        }
    }
    std::cout << std::endl;
    return 0;
}