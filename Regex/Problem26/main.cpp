#include <gsl/gsl>
#include <iostream>

std::string join(std::unique_ptr<std::string[]>&& lists, size_t size) {
    std::string result;
    for (size_t i = 0; i < size; ++i) {
        if (i > 0) {
            result += ' ';
        }
        result += lists[i];
    }

    return result;
}

int main() {
    size_t num_input;
    std::cin >> num_input;

    if (num_input < 1) {
        std::cout << "usage: [INT >= 1] [STRING; PREV_NUM]" << std::endl;
        return 1;
    }

    auto lists = std::make_unique<std::string[]>(num_input);
    for (size_t i = 0; i < num_input; ++i) {
        std::cin >> lists[i];
    }

    std::cout << '[' << join(std::move(lists), num_input) << ']' << std::endl;
    return 0;
}