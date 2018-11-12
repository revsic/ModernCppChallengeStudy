#include <gsl/gsl>
#include <filesystem>
#include <iostream>
#include <limits>
#include <regex>
#include <vector>

namespace fs = std::filesystem;

struct Entry {
    std::regex re;
    std::vector<fs::path> vec;

    template <typename... T>
    void emplace_back(T&&... args) {
        vec.emplace_back(std::forward<T>(args)...);
    }

    bool match(const std::string& path) {
        std::smatch match;
        return std::regex_match(path, match, re); // && match.size() > 0;
    }
};

void find_entry(Entry& entry, const fs::path& path) {
    if (entry.match(fs::absolute(path).string())) {
        entry.emplace_back(path);
    }

    if (fs::is_directory(path)) {
        for (auto const& dir : fs::directory_iterator(path)) {
            find_entry(entry, dir.path());
        }
    }
}

int main(int argc, char* argv[])
{
    std::string given;
    std::cin >> given;

    fs::path path(given);
    if (!fs::exists(path)) {
        std::cout << "invalid file path" << std::endl;
        return 1;
    }

    std::string s_regex;
    std::cin >> s_regex;
    
    Entry entry;
    entry.re = std::regex(s_regex);

    find_entry(entry, path);
    for (auto const& p : entry.vec) {
        std::cout << p << std::endl;
    }

    return 0;
}
