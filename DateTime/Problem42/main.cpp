#include <gsl/gsl>
#include <iostream>

int n_day_in_year(int year) {
    if (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0))
    {
        return 366;
    }
    else {
        return 365;
    }
}

int n_week_in_year(int year) {
    int day = 1;
    int month = 1;

    int front = year / 100;
    int back = year % 100;

    // Sat 0 ~ Fri 6
    int h = (day + (month + 1) * 26 / 10 + back + back / 4 + front / 4 - 2 * front) % 7;
   
    if (h == 1 && n_day_in_year(year) == 366) {
        return 54;
    }
    else {
        return 53;
    }
}

int main() {
    int year;
    std::cin >> year;

    std::cout << n_day_in_year(year) << ' '
              << n_week_in_year(year) << std::endl;
}
