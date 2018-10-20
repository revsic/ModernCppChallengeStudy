#include <gsl/gsl>
#include <cmath>
#include <iostream>

int narcissistic(int number) {
    int sum = 0;
    int digit = std::log10(number) + 1;
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
