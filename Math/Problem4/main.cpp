#include <gsl/gsl>
#include <iostream>
#include <memory>

int main(int argc, char* argv[])
{
    int limit = 0;
    std::cin >> limit;

    if (limit <= 2) {
        std::cout << "usage: [NUMBER > 2]" << std::endl;
        return 1;
    }

    auto dp = std::make_unique<bool[]>(limit);
    for (int i = 0; i < limit; ++i) {
        dp[i] = false;
    }

    int start = 2;
    while (true) {
        for (int i = start * 2; i < limit; i += start) {
            dp[i] = true;
        }

        while (start < limit && dp[++start]);
        if (start == limit) {
            break;
        }
    }

    int last_prime = limit;
    while (dp[--last_prime]);

    std::cout << last_prime << std::endl;
    return 0;
}
