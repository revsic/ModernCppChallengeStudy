#include <gsl/gsl>
#include <iostream>

template <typename F>
struct Foldr {
    F func;

    template <typename Fs>
    constexpr Foldr(Fs&& func) : func(std::forward<Fs>(func)) {
        // Do Nothing
    }

    template <typename T, typename U>
    constexpr auto impl(T&& arg1, U&& arg2) {
        return func(std::forward<T>(arg1), std::forward<U>(arg2));
    }

    template <typename T, typename... Ts>
    constexpr auto impl(T&& init, Ts&&... rest) {
        return func(std::forward<T>(init), impl(std::forward<Ts>(rest)...));
    }

    template <typename... Ts>
    constexpr auto operator()(Ts&&... args) {
        return impl(std::forward<Ts>(args)...);
    }
};

template <typename F>
constexpr auto foldr(F&& func) {
    return Foldr<F>(std::forward<F>(func));
}

template <typename T>
constexpr T min(T a, T b) {
    return a < b ? a : b;
}

int main() {
    std::cout << foldr(min<int>)(3, 1, 5, 2, 4) << std::endl;
    std::cout << foldr(min<std::string_view>)("abc", "zef", "qwe") << std::endl;

    auto add = [](int a, int b) constexpr { return a + b; };
    static_assert(foldr(add)(1, 2, 3, 4, 5) == 15);

    return 0;
}
