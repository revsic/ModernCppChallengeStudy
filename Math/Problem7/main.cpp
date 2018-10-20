#include <gsl/gsl>
#include <array>
#include <cmath>
#include <iostream>

int sum_divisor(int number) {
    int sum = 1;
    int bound = sqrt(number);

    if (bound * bound == number) {
        sum += bound;
        bound -= 1;
    }

    for (int i = 2; i <= bound; ++i) {
        if (number % i == 0) {
            sum += i + number / i;
        }
    }

    return sum;
}

template <size_t size>
int amicable_number(int number, std::array<bool, size>& table) {
    table[number] = true;
    int sum = sum_divisor(number);

    if (sum < size && !table[sum]) {
        int other = sum_divisor(sum);
        if (other == number) {
            table[other] = true;
            return sum;
        }
    }
    return 0;
}

int main(int argc, char* argv[])
{
    constexpr size_t maximum = 1000000;
    std::array<bool, maximum> table = { true, true, };
    
    for (int i = 2; i < maximum; ++i) {
        if (!table[i]) {
            int result = amicable_number(i, table);
            if (result) {
                std::cout << '(' << i << ", " << result << ')' << std::endl;
            }
        }
    }

    return 0;
}
