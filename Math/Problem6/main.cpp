//#include <gsl/gsl>

#include <cmath>
#include <iostream>
#include <numeric>
#include <vector>

int main(int argc, char* argv[])
{
    int limit = 0;
    std::cin >> limit;

    if (limit < 0) {
        std::cout << "usage: [POSITIVE_NUM]" << std::endl;
        return 1;
    }

    for (int i = 2; i < limit; ++i) {
        std::vector<int> divisors;
        divisors.emplace_back(1);

        int bound = std::sqrt(i);
        if (bound * bound == i) {
            divisors.emplace_back(bound);
            bound -= 1;
        }

        for (int div = 2; div <= bound; ++div) {
            if (i % div == 0) {
                divisors.emplace_back(div);
                divisors.emplace_back(i / div);
            }
        }

        int sum = std::accumulate(divisors.begin(), divisors.end(), 0);
        if (sum > i) {
            std::cout << '(' << i << ", " << sum - i << ')' << std::endl;
        }
    }

    return 0;
}
