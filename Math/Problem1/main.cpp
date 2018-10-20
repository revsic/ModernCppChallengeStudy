#include <gsl/gsl>
#include <iostream>

template <int n>
int sum_of(int target) {
    while (target % n) --target;
    target /= n;
    return n * target * (1 + target) / 2;
}

int main(int argc, char* argv[])
{
    int input = 0;
    std::cin >> input;

    int sum1 = sum_of<3>(input - 1) + sum_of<5>(input - 1) - sum_of<15>(input - 1);

    int sum2 = 0;
    for (int i = 1; i < input; ++i) {
        if (i % 3 == 0 || i % 5 == 0) {
            sum2 += i;
        }
    }
    std::cout << sum1 << ' ' << sum2 << std::endl;

    return 0;
}
