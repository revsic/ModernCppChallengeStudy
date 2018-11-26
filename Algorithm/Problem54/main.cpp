#include <iostream>
#include <tuple>
#include <vector>

template <typename T>
auto pairwise(std::vector<T> const& vec) {
    std::vector<std::tuple<T, T>> pairs;
    for (size_t i = 0; i < vec.size() / 2; ++i) {
        pairs.emplace_back(vec[i * 2], vec[i * 2 + 1]);
    }
    return pairs;
}

int main() {
    std::vector<int> v1 = { 1, 2, 3, 4, 5, 6, 7 };
    for (auto const&[a, b] : pairwise(v1)) {
        std::cout << "{ " << a << ", " << b << " }" << std::endl;
    }
    return 0;
}