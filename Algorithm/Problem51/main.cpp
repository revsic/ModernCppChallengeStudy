#include <iostream>
#include <vector>
#include <string>

int find_region_num(std::string const& num) {
    size_t start = 0;
    if (num[0] == '+') {
        start = 1;
    }
    std::string n = num.substr(start, 2);
    
    int front = -1;
    try {
        front = std::stoi(n);
    } catch(...) { }

    return front;
}

auto transform_phone(std::vector<std::string> const& vec, int region_number) {
    std::vector<std::string> transformed;
    for (auto const& num : vec) {
        size_t offset = 0;
        std::string new_num = '+' + std::to_string(region_number);
        if (num[0] == '+') {
            offset += 1;
        }

        if (find_region_num(num) == region_number) {
            offset += 2;
        }

        while(num[offset] == '0') ++offset;

        for (char n : num.substr(offset)) {
            if (n >= '0' && n <= '9') {
                new_num.push_back(n);
            }
        }

        transformed.push_back(std::move(new_num));
    }
    return transformed;
}

int main() {
    std::vector<std::string> vec = {
        "07555 123456",
        "07555123456",
        "+44 7555 123456",
        "44 7555 123456",
        "7555 123456"
    };

    for (auto const& num : transform_phone(vec, 44)) {
        std::cout << num << std::endl;
    }
    
    return 0;
}