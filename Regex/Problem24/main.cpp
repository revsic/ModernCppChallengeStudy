#include <gsl/gsl>
#include <iomanip>
#include <iostream>
#include <memory>
#include <sstream>

using BYTE = unsigned char;

auto conversion(const std::string& input) -> std::unique_ptr<BYTE[]> {
    assert(input.size() % 2);

    size_t num_bytes = input.size() / 2;
    auto ptr = std::make_unique<BYTE[]>(num_bytes);
    
    std::stringstream sstream(input);
    for (size_t i = 0; i < num_bytes; ++i) {
        int byte = 0;
        sstream >> std::hex >> byte;

        input[i] = static_cast<BYTE>(byte);
    }

    return std::make_tuple(std::move(ptr), num_bytes);
}

int main(int argc, char* argv[])
{
    std::string test[] = { "BAADF00D", "baadF00D", "010203040506" };

    for (const auto& str : test) {
        auto[ptr, size] = conversion(str);
        for (size_t i = 0; i < size; ++i) {
            std::cout << std::hex << std::setw(2) << static_cast<int>(ptr[i]) << ' ';
        }
        std::cout << std::endl;
    }

    return 0;
}
