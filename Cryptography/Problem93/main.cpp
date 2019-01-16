
#include <botan/rng.h>
#include <botan/auto_rng.h>
#include <botan/cipher_mode.h>
#include <botan/hex.h>

#include <fstream>
#include <iostream>
#include <iterator>
#include <string>

template <typename T, typename U>
auto encrypt(T const& input, U const& key) {
    Botan::AutoSeeded_RNG rng;
    auto cipher = Botan::Cipher_Mode::create("AES-128/CBC/PKCS7", Botan::ENCRYPTION);
    
    Botan::secure_vector<uint8_t> copied(input.begin(), input.end());
    Botan::secure_vector<uint8_t> key_(key.begin(), key.end());
    auto nonce = rng.random_vec(cipher->default_nonce_length());

    cipher->set_key(key_);
    cipher->start(nonce);
    cipher->finish(copied);

    return std::make_tuple(std::move(copied), std::move(nonce));
}

template <typename T, typename U, typename V>
auto decrypt(T const& input, U const& key, V const& nonce) {
    auto cipher = Botan::Cipher_Mode::create("AES-128/CBC/PKCS7", Botan::DECRYPTION);
    
    Botan::secure_vector<uint8_t> copied(input.begin(), input.end());
    Botan::secure_vector<uint8_t> key_(key.begin(), key.end());
    Botan::secure_vector<uint8_t> nonce_(nonce.begin(), nonce.end());

    cipher->set_key(key_);
    cipher->start(nonce_);
    cipher->finish(copied);

    return copied;
}

std::vector<char> read_from(std::string const& path) {
    std::ifstream file(path, std::ios::in | std::ios::binary);
    std::vector<char> buffer;
    
    std::copy(std::istreambuf_iterator<char>(file),
              std::istreambuf_iterator<char>(),
              std::back_inserter(buffer));
    file.close();

    return buffer;
}

template <typename T>
void write_to(std::string const& path, T const& cont) {
    std::ofstream ofs(path, std::ios::out | std::ios::binary);
    ofs << std::string(cont.begin(), cont.end());
    ofs.close();
}

int main() {
    std::string path, mode;
    std::cin >> path >> mode;

    std::vector<char> buffer = read_from(path);

    if (mode == "encrypt") {
        Botan::AutoSeeded_RNG rng;
        auto key = rng.random_vec(16);
        auto[encrypted, nonce] = encrypt(buffer, key);

        write_to(path + ".enc", encrypted);
        write_to(path + ".enc.key", key);
        write_to(path + ".enc.nonce", nonce);
    }
    else if (mode == "decrypt") {
        std::vector<char> key = read_from(path + ".key");
        std::vector<char> nonce = read_from(path + ".nonce");

        auto res = decrypt(buffer, key, nonce);
        write_to(path + ".dec", res);
    }
}