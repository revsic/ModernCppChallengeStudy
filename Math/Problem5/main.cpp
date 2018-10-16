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

    dp[0] = dp[1]= true;

    int start = 2;
    while (true) {
        if (start > 6 && !dp[start - 6]) {
            std::cout << '(' << start - 6 << ", " << start << ')' << std::endl;
        }

        for (int i = start * 2; i < limit; i += start) {
            dp[i] = true;
        }
        
        while (start < limit && dp[++start]);
        if (start == limit) {
            break;
        }
    }

    return 0;
}
