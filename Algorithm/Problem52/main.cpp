#include <iostream>
#include <string>
#include <vector>
#include <list>

auto permutation(std::string const& str, size_t num) {
    using Node = std::tuple<std::string, std::vector<char>>;

    std::vector<std::string> permut;
    std::vector<Node> stack = { 
        { "", std::vector<char>(str.begin(), str.end()) } 
    };

    while (!stack.empty()) {
        auto[substr, rest] = std::move(stack.back());
        stack.pop_back();

        if (substr.size() == num) {
            permut.emplace_back(std::move(substr));
            continue;
        }

        for (size_t i = 0; i < rest.size(); ++i) {
            auto vec = rest;
            vec.erase(vec.begin() + i);
            stack.emplace_back(substr + rest[i], std::move(vec));
        }
    }

    return permut;
}

int main() {
    std::string given = "ABCD";
    for (auto const& elem : permutation(given, 3)) {
        std::cout << elem << std::endl;
    }
}