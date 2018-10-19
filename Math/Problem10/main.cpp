#include <gsl/gsl>
#include <iostream>

template <size_t size>
int binary(int num, int* normal) {
    for (int i = size - 1; i >= 0; --i) {
        normal[i] = num % 2;
        num /= 2;
    }
    return 0;
}

template <size_t size>
int mirror(int num_digit, int gray_code[size][1 << size]) {
    int length = 1 << num_digit;
    for (int i = 0; i < num_digit; ++i) {
        for (int j = 0; j < length; ++j) {
            gray_code[i][length + j] = gray_code[i][length - j - 1];
        }
    }

    for (int i = 0; i < length; ++i) {
        gray_code[num_digit][i] = 0;
        gray_code[num_digit][length + i] = 1;
    }

    return 0;
}

int main(int argc, char* argv[])
{
    constexpr size_t digit = 5;
    constexpr size_t length = 1 << digit;
    
    int normal[length][digit] = { 0, };
    for (int i = 0; i < length; ++i) {
        binary<digit>(i, normal[i]);
    }

    int gray_code[digit][length] = { 0, 1, };
    for (int i = 1; i < digit; ++i) {
        mirror<digit>(i, gray_code);
    }

    for (int i = 0; i < length; ++i) {
        for (int j = digit - 1; j >= 0; --j) {
            std::cout << gray_code[j][i];
        }

        std::cout << ' ';
        for (int j = 0; j < digit; ++j) {
            std::cout << normal[i][j];
        }

        std::cout << ' ' << i << std::endl;
    }

    return 0;
}
