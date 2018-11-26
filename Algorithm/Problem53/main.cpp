#include <algorithm>
#include <iostream>
#include <vector>

double avg_rating(std::vector<int> const& vec) {
    std::vector<int> copied(vec);
    std::sort(copied.begin(), copied.end());

    int n_trunc = copied.size() / 20;
    for (size_t i = 0; i < n_trunc; ++i) {
        copied.erase(copied.begin());
        copied.erase(copied.end() - 1);
    }

    int sum = 0;
    for (int elem : copied) {
        sum += elem;
    }

    return static_cast<double>(sum) / copied.size();
}

int main() {
    std::vector<int> ratings[] = {
        { 10, 9, 10, 9, 9, 8, 7, 10, 5, 9, 9, 8 },
        { 10, 5, 7, 8, 9, 8, 9, 10, 10, 5, 9, 8, 10 },
        { 10, 10, 10, 9, 3, 8, 8, 9, 6, 4, 7, 10 },
        { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 },
    };

    for (auto const& vec : ratings) {
        std::cout << avg_rating(vec) << std::endl;
    }
    return 0;
}