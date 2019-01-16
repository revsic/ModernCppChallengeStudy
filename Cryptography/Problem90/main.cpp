#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

std::vector<bool> to_bit(size_t idx, size_t size) {
    std::vector<bool> bits;
    for (int i = size - 1; i >= 0; --i) {
        bits.push_back(static_cast<bool>(idx & (1 << i)));
    }
    return bits;
}

std::vector<size_t> from_bits(size_t size, std::vector<bool> const& bits) {
    size_t accum = 0;
    std::vector<size_t> res;
    for (size_t i = 0; i < bits.size(); ++i) {
        accum += static_cast<size_t>(bits[i]) * (1 << (size - 1 - i % size));
        if ((i + 1) % size == 0) {
            res.push_back(accum);
            accum = 0;
        }
    }

    if (bits.size() % size != 0) {
        res.push_back(accum);
    }
    return res;
}

std::string encode(std::string const& input) {
    std::string const table = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    
    std::vector<bool> bits;
    for (char c : input) {
        std::vector<bool> res = to_bit(c, 8);
        bits.insert(bits.end(), res.begin(), res.end());
    }

    std::vector<size_t> res = from_bits(6, bits);

    std::string output;
    output.resize(res.size());

    std::transform(res.begin(), res.end(), output.begin(), 
                   [&](size_t idx) { return table[idx]; });

    if (bits.size() % 6 != 0) {
        for (size_t i = 0; i < 3 - (bits.size() % 6) / 2; ++i) {
            output.push_back('=');
        }
    }

    return output;
}

std::string decode(std::string const& input) {
    std::string const table = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

    size_t end = input.size();
    for (; input[end - 1] != '='; --end);

    std::vector<bool> bits;
    for (size_t i = 0; i < end; ++i) {
        size_t idx = std::distance(table.begin(), 
                                   std::find(table.begin(), table.end(), input[i])); 
        std::vector<bool> res = to_bit(idx, 6);
        bits.insert(bits.end(), res.begin(), res.end());
    }

    std::vector<size_t> res = from_bits(8, bits);
    return std::string(res.begin(), res.end());
}

int main() {
    std::string input;
    std::cin >> input;

    std::string encoded = encode(input);
    std::cout << encoded << std::endl;
    std::cout << decode(encoded) << std::endl;
}