#include <cctype>
#include <iostream>
#include <string>

int main() {
    std::string given;
    std::getline(std::cin, given);

    size_t nums[26] = { 0, };

    size_t total = 0;
    for (char c : given) {
        if (!std::isalpha(c)) {
            continue;
        }

        if (std::isupper(c)) {
            c = std::tolower(c);
        }

        total += 1;
        nums[c - 'a'] += 1;
    }

    for (size_t i = 0; i < 26; ++i) {
        double rate = static_cast<double>(nums[i]) / total * 100;
        int quant = static_cast<int>(rate);

        std::cout << static_cast<char>('a' + i) << ' ';
        for (size_t j = 0; j < quant; ++j) {
            std::cout << '*';
        }
        std::cout << '\n';
    }
}