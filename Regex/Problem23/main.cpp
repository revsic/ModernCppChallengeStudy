#include <gsl/gsl>
#include <iomanip>
#include <iostream>
#include <sstream>

using BYTE = unsigned char;

auto conversion(const BYTE* seq, size_t size) {
    std::stringstream sstream;
    sstream << std::uppercase << std::setfill('0') << std::hex;
    for (size_t i = 0; i < size; ++i) {
        sstream << std::setw(2) << static_cast<int>(seq[i]);
    }
    std::string upper = sstream.str();

    sstream.str(std::string());
    sstream << std::nouppercase;
    for (size_t i = 0; i < size; ++i) {
        sstream << std::setw(2) << static_cast<int>(seq[i]);
    }
    std::string lower = sstream.str();

    return std::make_tuple(std::move(upper), std::move(lower));
}

int main(int argc, char* argv[])
{
    BYTE test[] = { 0xBA, 0xAD, 0xF0, 0x0D };
    BYTE test2[] = { 1, 2, 3, 4, 5, 6 };

    auto[test1_upper, test1_lower] = conversion(test, 4);
    std::cout << test1_upper << ' ' << test1_lower << std::endl;

    auto[test2_upper, test2_lower] = conversion(test2, 6);
    std::cout << test2_upper << ' ' << test2_lower << std::endl;

    return 0;
}
