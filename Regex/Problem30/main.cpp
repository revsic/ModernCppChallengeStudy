#include <gsl/gsl>
#include <iostream>
#include <regex>

class URL {
public:
    URL(const std::string& url)
    {
        std::smatch match;
        if (std::regex_search(url, match, format); match.size() > 0) {
            m_protocol = match[2];
            m_domain = match[3];
            m_port = match[5];
            m_path = match[7];
            m_query = match[9];
            m_fragment = match[11];
        }
    }

    friend std::ostream& operator<<(std::ostream& stream, const URL& url) {
        std::cout << "{ protocol : " << url.m_protocol 
                  << ", domain : " << url.m_domain
                  << ", port : " << url.m_port
                  << ", path : " << url.m_path
                  << ", query: " << url.m_query
                  << ", fragment: " << url.m_fragment 
                  << " }";
        return stream;
    }

private:
    std::string m_protocol;
    std::string m_domain;
    std::string m_port;
    std::string m_path;
    std::string m_query;
    std::string m_fragment;

    static const std::regex format;
};
const std::regex URL::format("(([^:]+)://)?([^:/]+)(:([0-9]+))?(/([^\\?#]+))?(\\?([^#]+))?(#(.+))?");

int main() {
    while (true) {
        std::string given;
        std::getline(std::cin, given);

        URL url(given);
        std::cout << url << std::endl;
    }
}