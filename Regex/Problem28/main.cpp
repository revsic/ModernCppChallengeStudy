#include <gsl/gsl>
#include <iostream>

int main() {
    std::string input;
    std::cin >> input;

    std::string subseq;

    size_t size = input.size();
    for (size_t i = 0; i < size; ++i) {
        size_t j = 0;
        size_t limit = std::min(i, size - i - 1);
        for (; j <= limit; ++j) {
            if (input[i + j] != input[i - j]) {
                break;
            }
        }

        j -= 1;
        size_t new_size = 2 * j + 1;
        if (subseq.size() < new_size) {
            subseq = input.substr(i - j, new_size);
        }
    }

    std::cout << subseq << std::endl;
    return 0;
}