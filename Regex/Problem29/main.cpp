#include <gsl/gsl>
#include <iostream>
#include <regex>

class License {
public:
    License(const std::string& str) : m_str(str) {
        // Do Nothing
    }

    License(std::string&& str) : m_str(std::move(str)) {
        // Do Nothing
    }

    bool validate() {
        std::smatch match;
        if (std::regex_search(m_str, match, format) && match.size() > 0) {
            return m_str == match[0];
        }
        return false;
    }

    std::vector<std::string> extract() {
        std::vector<std::string> result;
        for (auto iter = std::sregex_iterator(m_str.begin(), m_str.end(), format);
             iter != std::sregex_iterator(); ++iter)
        {
            result.emplace_back((*iter).str());
        }
        return result;
    }

private:
    std::string m_str;
    static std::regex format;
};
std::regex License::format("([A-Z]{3}\\-[A-Z]{2} [0-9]{3})");

int main() {
    std::string str;
    std::getline(std::cin, str);

    License license(str);
    for (auto const& l : license.extract()) {
        std::cout << l << std::endl;
    }
    return 0;
}