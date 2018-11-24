#include <iostream>
#include <vector>
#include <string>

auto filter_list(std::vector<std::string> const& vec, int region_num) {
    std::vector<std::string> filtered;
    for (auto const& num : vec) {
        if (num.size() < 3) {
            continue;
        }

        size_t start = 0;
        if (num[0] == '+') {
            start = 1;
        }

        std::string n = num.substr(start, 2);
        try {
            size_t ptr = 0;
            if (std::stoi(n, &ptr) == region_num) {
                filtered.emplace_back(num);
            }
        } catch(...) {}
    }
    return filtered;
}

int main() {
    std::vector<std::string> vec = {
        "+821012345678",
        "821012345678",
        "01012345678",
        "+82-10-1234-5678",
        "82-10-1234-4567",
        "010-1234-5678"
    };

    for (auto const& num : filter_list(vec, 82)) {
        std::cout << num << std::endl;
    }
}