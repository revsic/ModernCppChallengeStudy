#include <iostream>
#include <functional>

template <typename Rules>
auto validate(std::string const& view, Rules const& rules) {
    for (auto iter = std::begin(rules); iter != std::end(rules); ++iter) {
        if (!(*iter)(view)) {
            return iter;
        }
    }
    return std::end(rules);
}

auto min_length(size_t len) {
    return [=](std::string const& str) { return str.size() > len; };
}

template <typename Rule>
auto presence(Rule&& rule) {
    return [rule = std::forward<Rule>(rule)]
           (std::string const& str)
        {
            for (char c : str) {
                if (rule(c)) return true;
            }
            return false;
        };
}

int main()
{
    std::function<bool(std::string const&)> rules[] = {
        min_length(10),
        presence([](char c) { return std::isupper(c); }),
        presence([](char c) { return std::islower(c); }),
        presence([](char c) { return std::isdigit(c); })
    };

    std::string input;
    std::cin >> input;

    if (auto iter = validate(input, rules); iter == std::end(rules)) {
        std::cout << input << " pass" << std::endl;
    }
}
