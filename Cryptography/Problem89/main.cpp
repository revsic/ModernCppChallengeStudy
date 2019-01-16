#include <iostream>
#include <string>

std::string encrypt(std::string const& input, std::string const& keyword) {
    std::string output;
    output.reserve(input.size());

    auto get_idx = [](char c) { return c - (isupper(c) ? 'A' : 'a'); };

    for (size_t i = 0; i < input.size(); ++i) {
        size_t key_idx = (get_idx(keyword[i % keyword.size()]) + 25) % 26;
        size_t input_idx = get_idx(input[i]);
        output.push_back('A' + (1 + key_idx + input_idx) % 26);
    }
    return output;
}

std::string decrypt(std::string const& input, std::string const& keyword) {
    std::string output;
    output.reserve(input.size());

    auto get_idx = [](char c) { return c - (isupper(c) ? 'A' : 'a'); };

    for (size_t i = 0; i < input.size(); ++i) {
        size_t key_idx = (get_idx(keyword[i % keyword.size()]) + 25) % 26;
        size_t input_idx = get_idx(input[i]);
        output.push_back('A' + (input_idx - key_idx + 51) % 26);
    }
    return output;
}

int main() {
    std::string input, keyword;
    std::cin >> input >> keyword;

    std::string encrypted = encrypt(input, keyword);
    std::cout << encrypted << std::endl;
    std::cout << decrypt(encrypted, keyword) << std::endl;
}