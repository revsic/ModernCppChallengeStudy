#include <gsl/gsl>
#include <iostream>
#include <sstream>

struct Roman {
    int unit;
    char chr;
};

constexpr size_t ROMAN_SYMBOLS = 7;
Roman repr[ROMAN_SYMBOLS] = {
    { 1000, 'M', },
    { 500, 'D' },
    { 100, 'C' },
    { 50, 'L' },
    { 10, 'X' },
    { 5, 'V' },
    { 1, 'I' },
};

std::string roman(int number) {
    int prev = -1;
    std::stringstream stream;

    for (int i = 0; i < ROMAN_SYMBOLS; ++i) {
        int digit = number / repr[i].unit;
        if (digit != 0) {    
            if (digit == 4) {
                if (prev == i - 1) {
                    stream << repr[i].chr << repr[prev - 1].chr;
                }
                else {
                    stream << repr[i].chr << repr[prev].chr;
                }
            }
            else {                                                                                                                                                                                                                         (digit == 4) {
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
