#include <gsl/gsl>
#include <iomanip>
#include <iostream>
#include <memory>

using BYTE = unsigned char;

auto conversion(const std::string& input) {
    size_t size = input.size();
    assert(size % 2 == 0);

    size_t num_bytes = size / 2;
    auto ptr = std::make_unique<BYTE[]>(num_bytes);
    
    for (size_t i = 0; i < size; i += 2) {
        int byte = std::stoi(input.substr(i, 2), nullptr, 16);
        ptr[i / 2] = static_cast<BYTE>(byte);
    }

    return std::make_tuple(std::move(ptr), num_bytes);
}

int main(int argc, char* argv[])
{
    std::string test[] = { "BAADF00D", "baadF00D", "010203040506" };

    std::cout << std::hex << std::setfill('0');
    for (const auto& str : test) {
        auto[ptr, size] = conversion(str);
        for (size_t i = 0; i < size; ++i) {
            std::cout << std::setw(2) << static_cast<int>(ptr[i]) << ' ';
        }
        std::cout << std::endl;
    }

    return 0;
}
