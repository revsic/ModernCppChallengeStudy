#include <botan/hash.h>
#include <botan/hex.h>

#include <fstream>
#include <iostream>
#include <iterator>
#include <string>

template <typename T>
std::string hash(T const& input, std::string const& type) {
    std::unique_ptr<Botan::HashFunction> hash(Botan::HashFunction::create(type));
    std::vector<uint8_t> data(input.begin(), input.end());
    
    hash->update(data.data(), data.size());
    return Botan::hex_encode(hash->final());
}

int main() {
    std::string path;
    std::cin >> path;

    std::ifstream file(path, std::ios_base::binary);
    std::vector<char> buffer;
    
    std::copy(std::istreambuf_iterator<char>(file),
              std::istreambuf_iterator<char>(),
              std::back_inserter(buffer));

    std::cout << "SHA-256: " << hash(buffer, "SHA-256") << std::endl;
    std::cout << "MD5: " << hash(buffer, "MD5") << std::endl;
}