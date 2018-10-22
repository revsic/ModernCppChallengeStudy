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
                m_octets[i] = std::stoi(match.str(i + 1));
            }
        }
    }

    operator std::string() const {
        std::stringstream sstream;
        for (int i = 0; i < 4; ++i) {
            if (i != 0) {
                sstream << '.';
            }
            sstream << static_cast<int>(m_octets[i]);
        }
        return sstream.str();
    }

    IPv4& operator++() {
        m_octets[3] += 1;
        for (int i = 3; i > 0; --i) {
            if (m_octets[i] == 0) {
                m_octets[i - 1] += 1;
            }
            else {
                break;
            }
        }
        return *this;
    }

    bool operator<(const IPv4& other) {
        for (int i = 0; i < 4; ++i) {
            if (m_octets[i] < other.m_octets[i]) {
                return true;
            }
        }
        return false;
    }

    friend std::ostream& operator<<(std::ostream& stream, const IPv4& ip) {
        stream << std::string(ip);
        return stream;
    }

private:
    static const std::regex ip_regex;
    OCTET m_octets[4]= { 0, };
};

const std::regex IPv4::ip_regex("([0-9]{1,3})\\.([0-9]{1,3})\\.([0-9]{1,3})\\.([0-9]{1,3})");

int main(int argc, char* argv[])
{
    std::string s_from, s_to;
    std::cin >> s_from >> s_to;

    IPv4 ip_from(s_from), ip_to(s_to);
    for (; ip_from < ip_to; ++ip_from) {
        std::cout << ip_from << ' ';
    }
    std::cout << std::endl;

    return 0;
}
