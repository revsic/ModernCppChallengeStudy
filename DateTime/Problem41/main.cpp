#include <gsl/gsl>
#include <iostream>

int main() {
    int y, m, d;
    std::cin >> y >> m >> d;

    int front = y / 100;
    int back = y % 100;

    // https://en.wikipedia.org/wiki/Determination_of_the_day_of_the_week#Zeller%E2%80%99s_algorithm
    int h = (d + (m + 1) * 26 / 10 + back + back / 4 + front / 4 - 2 * front) % 7;
    const char* week[] = { "Sat", "Sun", "Mon", "Tue", "Wed", "Thu", "Fri" };

    std::cout << week[h] << std::endl;
}