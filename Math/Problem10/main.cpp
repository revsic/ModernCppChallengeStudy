//#include <gsl/gsl>
#include <iostream>
#include <memory>
#include <tuple>

auto to_binary(int num) {
    size_t num_digit = 0;
    for (int digit = 1; digit <= num; digit <<= 1, ++num_digit);

    auto data = std::make_unique<int[]>(num_digit);
    for (int i = num_digit - 1; i >= 0; --i) {
        data[i] = num % 2;
        num /= 2;
    }

    return std::make_tuple(std::move(data), num_digit);
}

auto bin_to_gray(std::unique_ptr<int[]>&& binary, size_t size) {
    for (int i = 0; i < size - 2; ++i) {
        binary[i] ^= binary[i + 1];
    }
    return std::move(binary);
}

int gray_to_int(std::unique_ptr<int[]>&& gray, size_t size) {
    for (int i = size - 2; i >= 0; --i) {
        gray[i] ^= gray[i + 1];
    }

    int num = 0;
    for (int i = 0; i < size; ++i) {
        num += gray[i] * (1 << i);
    }

    return num;
}

int main(int argc, char* argv[]) {
    constexpr size_t digit = 5;

    for (int i = 0; i < digit; ++i) {
        auto[binary, size] = to_binary(i);
        for (int j = 0; j < size; ++j) {
            std::cout << binary[j];
        }
        std::cout << ' ';
        
        auto gray_code = bin_to_gray(std::move(binary), size);
        for (int j = 0; j < size; ++j) {
            std::cout << gray_code[j];
        }
        
        std::cout << ' ' << gray_to_int(std::move(gray_code), size);
    }

    return 0;
}
