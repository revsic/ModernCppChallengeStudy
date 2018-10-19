#include <gsl/gsl>
#include <iostream>
#include <sstream>

struct Roman {
    int unit;
    char chr;
};

constexpr size_t ROMAN_SYMBOLS = 11;
Roman repr[ROMAN_SYMBOLS] = {
    { 1000000, 'M' },
    { 500000, 'D' },
    { 100000, 'C' },
    { 5000, 'V' },
    { 1000, 'm', },
    { 500, 'd' },
    { 100, 'c' },
    { 50, 'l' },
    { 10, 'x' },
    { 5, 'v' },
    { 1, 'i' },
};

std::string roman(int number) {
    int prev = -1;
    std::stringstream stream;

    for (int i = 0; i < ROMAN_SYMBOLS; ++i) {
        int digit = number / repr[i].unit;
        if (digit != 0) {    
            if (digit == 4) {
                if (prev == i - 1) {
                    std::string temporal = stream.str();
                    temporal.pop_back();
                    
                    stream.str(std::string());
                    stream << temporal << repr[i].chr << repr[i - 2].chr;
                }
                else {
                    stream << repr[i].chr << repr[i - 1].chr;
                }
            }
            else {
                for (int j = 0; j < digit; ++j) {
                    stream << repr[i].chr;
                } 
            }
            number %= repr[i].unit;
            prev = i;
        }
    }

    return stream.str();
}

int main(int argc, char* argv[])
{
    int given = 0;
    std::cin >> given;

    if (given < 1) {
        std::cout << "usage: [NUMBER > 0]" << std::endl;
        return 1;
    }

    std::cout << roman(given) << std::endl;
    return 0;
}
