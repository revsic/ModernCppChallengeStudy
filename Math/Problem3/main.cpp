#include <gsl/gsl>
#include <algorithm>
#include <iostream>
#include <memory>
#include <numeric>

int gcd(int a, int b) {
    do {
        if (a > b) {
            std::swap(a, b);
        }
        b %= a;
    } while (b != 0);

    return a;
}

int lcm(int a, int b) {
    return a * b / gcd(a, b);
}

int main(int argc, char* argv[])
{
    int len = 0;
    std::cout << "len: ";
    std::cin >> len;

    if (len < 2) {
        std::cout << "[*] length should be bigger than two" << std::endl;
        return 1;
    }

    auto data = std::make_unique<int[]>(len);
    for (int i = 0; i < len; ++i) {
        std::cin >> data[i];
        if (data[i] <= 0) {
            std::cout << "[*] number sould be positive" << std::endl;
        }
    }

    int* data_ptr = data.get();
    std::cout << std::accumulate(data_ptr, data_ptr + len, 1, lcm) << std::endl;

    return 0;
}
