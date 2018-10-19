#include <gsl/gsl>
#include <iostream>

using ull = unsigned long long;

constexpr size_t cache_size = 1000000;
ull cache[cache_size] = { 0, };

int main(int argc, char* argv[])
{
    ull max = 0;   
    int number = -1;

    for (int i = 2; i < 1000000; ++i) {
        int cnt = 0;
        ull num = i;

        while (num > 1) {
            if (num < cache_size && cache[num] != 0) {
                cnt += cache[num];
                break;
            }

            cnt += 1;
            if (num % 2 == 0) {
                num /= 2;
            }
            else {
                num = 3 * num + 1;
            }
        }

        cache[i] = cnt;
        if (cnt > max) {
            max = cnt;
            number = i;
        }
        
    }

    std::cout << number << ' ' << max + 1 << std::endl;
    return 0;
}
