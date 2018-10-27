#include <gsl/gsl>
#include <iostream>
#include <vector>

template <typename T, 
          typename IterType = decltype(std::declval<T>().begin())>
struct Enumerate {
    T object;
    IterType iter_begin;
    IterType iter_end;
    size_t size;

    Enumerate(T&& given) : 
        object(std::forward<T>(given)), 
        iter_begin(object.begin()), 
        iter_end(object.end()),
        size(std::distance(iter_begin, iter_end))
    {
        // Do Nothing
    }

    struct Iterator {
        IterType iter;
        size_t now;

        auto operator*() {
            return std::make_tuple(*iter, now);
        }

        Iterator& operator++() {
            ++iter;
            ++now;
            return *this;
        }

        bool operator!=(const Iterator& other) {
            return iter != other.iter && now != other.now;
        }
    };

    auto begin() const {
        return Iterator { iter_begin, 0 };
    }

    auto end() const {
        return Iterator { iter_end, size };
    }
};

template <typename T>
auto enumerate(T&& given) {
    return Enumerate<T>(std::forward<T>(given));
}

std::vector<std::string> split(const std::string& given, 
                                 const std::string& delim) 
{
    size_t start = 0;
    std::vector<std::string> splitted;

    for (auto const&[chr, idx] : enumerate(given)) {
        if (auto iter = std::find(delim.begin(), delim.end(), chr);
            iter != delim.end()) 
        {
            if (idx > start) {
                splitted.emplace_back(given.substr(start, idx - start));
            }
            start = idx + 1;
        }
    }

    if (start < given.size()) {
        splitted.emplace_back(given.substr(start, given.size() - start));
    }

    return splitted;
}

int main() {
    std::string given;
    std::getline(std::cin, given);

    std::string delim;
    std::getline(std::cin, delim);

    std::vector<std::string> result = split(given, delim);
    for (auto const& str : result) {
        std::cout << '[' << str << "] ";
    }
    std::cout << std::endl;

    return 0;
}