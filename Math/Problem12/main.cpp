#include <gsl/gsl>
#include <iostream>

using ull = unsigned long long;

constexpr size_t cache_size = 1000000;
ull cache[cache_size] = { 1, 1, };

int main(int argc, char* argv[])
{
    ull max = 0;   
    int number = -1;

    for (int i = 2; i < 1000000; ++i) {
        int cnt = 1;
        ull num = i;

        for (; num >= i; ++cnt) {
            if (num % 2 == 0) {
                num /= 2;
            }
            else {
                num = 3 * num + 1;
            }
        }

        cache[i] = cnt + cache[num] - 1;
        if (cache[i] > max) {
            max = cache[i];
            number = i;
        }
    }

    std::cout << number << ' ' << max << std::endl;
    return 0;
}
