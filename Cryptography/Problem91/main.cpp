#include <botan/hash.h>
#include <botan/hex.h>

#include <iostream>
#include <map>
#include <string>

class System {
public:
    enum class Status {
        INVALID = 0,
        INVALID_ID = 1,
        INVALID_PWD = 2,
        VALID = 3,
    };

    System() = default;

    void regist(std::string const& id, std::string const& pwd) {
        users[id] = sha1(pwd);        
    }

    Status validate(std::string const& id, std::string const& pwd) {
        if (auto iter = users.find(id); iter != users.end()) {
            if (iter->second == sha1(pwd)) {
                return Status::VALID;
            }
            else {
                return Status::INVALID_PWD;
            }
        }
        else {
            return Status::INVALID_ID;
        }
    }

private:
    std::map<std::string, std::string> users;

    std::string sha1(std::string const& input) {
        std::unique_ptr<Botan::HashFunction> hash(Botan::HashFunction::create("SHA-1"));
        std::vector<uint8_t> buf(input.begin(), input.end());

        hash->update(buf.data(), buf.size());
        return Botan::hex_encode(hash->final());
    } 
};

int main() {
    System system;
    system.regist("revsic", "ABCDabcd1234");

    std::string pwd;
    std::cin >> pwd;

    if (system.validate("revsic", pwd) == System::Status::VALID) {
        std::cout << "Valid password: " << pwd << std::endl;
    }
    else {
        std::cout << "Invalid password: " << pwd << std::endl;
    }
}