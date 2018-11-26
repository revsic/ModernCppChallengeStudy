#include <iostream>
#include <tuple>
#include <type_traits>
#include <vector>

template <typename T, typename U>
struct ZipIter {
    template <typename IterT, typename IterU>
    struct Iterator {
        IterT iter_t;
        IterU iter_u;

        Iterator(IterT&& iter_t, IterU&& iter_u) : iter_t(iter_t), iter_u(iter_u) {
            // Do Nothing
        }

        Iterator& operator++() {
            ++iter_t;
            ++iter_u;
            return *this;
        }

        auto operator*() {
            return std::make_tuple(*iter_t, *iter_u);
        }

        bool operator!=(Iterator const& iter) {
            return iter_t != iter.iter_t && iter_u != iter.iter_u;
        }
    };

    using Ts = std::decay_t<T>;
    using Us = std::decay_t<U>;

    using value_type = std::tuple<typename Ts::value_type, typename Us::value_type>;

    using reference = value_type&;
    using const_reference = value_type const&;

    using iterator = Iterator<typename Ts::iterator, typename Us::iterator>;
    using const_iterator = Iterator<typename Ts::const_iterator, typename Us::const_iterator>;

    T v1;
    U v2;

    ZipIter(T&& v1, U&& v2) : v1(std::forward<T>(v1)), v2(std::forward<U>(v2))
    {
        // Do Nothing
    }

    iterator begin() {
        return iterator(v1.begin(), v2.begin());
    }

    const_iterator begin() const {
        return const_iterator(v1.cbegin(), v2.cbegin());
    }

    iterator end() {
        return iterator(v1.end(), v2.end());
    }

    const_iterator end() const {
        return const_iterator(v1.cend(), v2.cend());
    }
};

template <typename T, typename U>
auto zip(T&& v1, U&& v2) {
    return ZipIter<T, U>(std::forward<T>(v1), std::forward<U>(v2));
}

int main() {
    std::vector<int> v1 = { 0, 1, 2, 3, 4, 5 };
    std::vector<std::string> v2 = { "ab", "cd", "ef", "gh" };

    for (auto const&[e1, e2] : zip(v1, v2)) {
        std::cout << e1 << ", " << e2 << std::endl;
    }

    return 0;
}