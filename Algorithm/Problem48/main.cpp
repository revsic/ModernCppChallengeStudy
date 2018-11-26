#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

template <typename Iter>
auto most_frequent_elem(Iter begin, Iter end) {
    using value_type = typename std::iterator_traits<Iter>::value_type;

    size_t max = 0;
    std::unordered_map<value_type, size_t> map;
    for (; begin != end; ++begin) {
        if (auto find = map.find(*begin); find != map.end()) {
            auto&[val, num] = *find;
            num += 1;
        }
        else {
            map[*begin] = 1;
        }
        max = std::max(max, map[*begin]);
    }

    std::vector<std::tuple<value_type, size_t>> vec;
    for (auto&[val, num] : map) {
        if (num == max) {
            vec.emplace_back(std::move(val), num);
        }
    }
    return vec;
}

int main() {
    int arr[] = { 1, 1, 3, 5, 8, 13, 3, 5, 8, 8, 5 };
    auto res = most_frequent_elem(std::begin(arr), std::end(arr));

    for (auto const&[val, num] : res) {
        std::cout << "val: " << val << ", num: " << num << '\n';
    }
    std::cout << std::endl;

    return 0;
}