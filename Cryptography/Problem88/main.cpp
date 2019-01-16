#include <iostream>
#include <string>

bool isupper(char c) {
    return c >= 'A' && c <= 'Z';
}

bool islower(char c) {
    return c >= 'a' && c <= 'z';
}

std::string encrypt(std::string const& input, size_t dist) {
    std::string output;
    output.reserve(input.size());

    for (char c : input) {
        if (isupper(c)) {
            c = 'A' + (c - 'A' + dist) % 26;
        }
        else if (islower(c)) {
            c = 'a' + (c - 'a' + dist) % 26;
        }
        output.push_back(c);
    }
    return output;
}

std::string decrypt(std::string const& input, size_t dist) {
    return encrypt(input, 26 - dist % 26);
}

int main(int argc, char* argv[])
{
    size_t dist;
    std::string input;
    std::cin >> input >> dist;

    std::string encrypted = encrypt(input, dist);
    std::cout << encrypted << std::endl;
    std::cout << decrypt(encrypted, dist) << std::endl;
}
