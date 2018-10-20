#include <gsl/gsl>
#include <iostream>
#include <memory>
#include <tuple>

struct Box {
    Box(size_t size, std::unique_ptr<int[]>&& bin, int placeholder = -1) :
        size(size), bin(std::move(bin)), placeholder(placeholder)
    {
        // Do Nothing
    }

    size_t size;
    std::unique_ptr<int[]> bin;

    int placeholder;
};

auto binary(int num, int placeholder = -1) {
    size_t size = 0;
    for (int digit = 1; digit <= num; digit <<= 1, ++size);
    
    auto bin = std::make_unique<int[]>(size);
    for (size_t i = size; i > 0; --i) {
        bin[i - 1] = num % 2;
        num /= 2;
    }
    
    return Box(size, std::move(bin), placeholder);
}

auto gray_code(Box&& box) {
    for (int i = box.size - 1; i > 0; --i) {
        box.bin[i] ^= box.bin[i - 1];
    }
    return std::move(box);
}

auto rollback(Box&& box) {
    for (int i = 1; i < box.size; ++i) {
        box.bin[i] ^= box.bin[i - 1];
    }
    return std::move(box);
}

int make_num(const Box& box) {
    int num = 0;
    for (int i = 1; i <= box.size; ++i) {
        num += box.bin[i - 1] << (box.size - i);
    }
    return num;
}

std::ostream& operator<<(std::ostream& stream, const Box& box) {
    for (int i = box.size; i < box.placeholder; ++i) {
        stream << 0;
    }

    for (int i = 0; i < box.size; ++i) {
        stream << box.bin[i];
    }
    
    return stream;
}

int main(int argc, char* argv[]) {
    constexpr size_t digit = 5;

    for (int i = 0; i < (1 << digit); ++i) {
        auto bin = binary(i, digit);
        std::cout << bin << ' ';

        auto gray = gray_code(std::move(bin));
        std::cout << gray << ' ';

        auto converted = rollback(std::move(gray));
        std::cout << converted << ' '
                  << make_num(converted) << std::endl;
    }

    return 0;
}
