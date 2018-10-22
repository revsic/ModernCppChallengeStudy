#include <gsl/gsl>
#include <iostream>
#include <regex>
#include <sstream>
#include <string>

class IPv4 {
public:
    using OCTET = unsigned char;

    IPv4() {}

    IPv4(const std::string& str) {
        std::smatch match;
        if (std::regex_search(str, match, IPv4::ip_regex) && match.size() == 5) {
            for (size_t i = 0; i < 4; ++i) {
                octets[i] = std::stoi(match.str(i + 1));
            }
        }
    }

    operator std::string() const {
        std::stringstream sstream;
        for (int i = 0; i < 4; ++i) {
            if (i != 0) {
                sstream << '.';
            }
            sstream << static_cast<int>(octets[i]);
        }
        return sstream.str();
    }

    friend std::ostream& operator<<(std::ostream& stream, const IPv4& ip) {
        stream << std::string(ip);
        return stream;
    }

private:
    static const std::regex ip_regex;
    OCTET octets[4]= { 0, };
};

const std::regex IPv4::ip_regex("([0-9]{1,3})\\.([0-9]{1,3})\\.([0-9]{1,3})\\.([0-9]{1,3})");

int main(int argc, char* argv[])
{
    std::string input;
    std::cin >> input;

    IPv4 ip(input);
    std::cout << ip << std::endl;

    return 0;
}
