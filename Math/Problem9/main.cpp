#include <gsl/gsl>
#include <iostream>
#include <memory>
#include <vector>

int generate_primes(int limit, std::vector<int>& primes) {
    auto dp = std::make_unique<bool[]>(limit + 1);
    for (int i = 0; i <= limit; ++i) {
        dp[i] = false;
    }

    int start = 2;
    while (true) {
        primes.emplace_back(start);

        for (int i = start * 2; i <= limit; i += start) {
            dp[i] = true;
        }

        while (start <= limit && dp[++start]);
        if (start > limit) {
            break;
        }
    }

    return 0;
}

int main(int argc, char* argv[])
{
    int given = 0;
    std::cin >> given;

    if (given < 2) {
        std::cout << "usage: [NUMBER >= 2]" << std::endl;
        return 1;
    }

    std::vector<int> primes;
    generate_primes(given, primes);

    for (int p : primes) {
        if (given % p == 0) {
            std::cout << p << ' ';

            while (given % p == 0) {
                given /= p;
            }
        }
    }
    std::cout << std::endl;

    return 0;
}
