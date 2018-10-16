#include <gsl/gsl>

#include <cmath>
#include <iostream>

int narcissistic(int number) {
    int digit = 0;
    for (int i = 1; number >= i; i *= 10, ++digit);

    int sum = 0;
    while (number) {
        sum += pow(number % 10, digit);
        number /= 10;
    }
    return sum;
}

int main(int argc, char* argv[])
{
    for (int i = 100; i < 1000; ++i) {
        if (i == narcissistic(i)) {
            std::cout << i << ' ';
        }
    }
    std::cout << std::endl;

    return 0;
}
