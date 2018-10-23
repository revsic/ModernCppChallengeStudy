#include <gsl/gsl>
#include <iostream>
#include <tuple>
#include <utility>

template <typename F>
struct Fold {
    F oper;

    template <typename T>
    struct Wrapper {
        F oper;
        T value;

        template <typename Fs, typename Ts>
        constexpr Wrapper(Fs&& oper, Ts&& value) : 
            oper(std::forward<Fs>(oper)), value(std::forward<Ts>(value)) 
        {
            // Do nothing
        }

        template <typename Ts, typename W>
        constexpr friend auto operator+(Ts&& value, const Wrapper<W>& wrapper) {
            return wrapper.oper(std::forward<Ts>(value), wrapper.value);
        }
    };

    template <typename Fs>
    constexpr Fold(Fs&& oper) : oper(std::forward<Fs>(oper)) {
        // DO Nothing
    }

    template <typename T, typename... Ts>
    constexpr auto operator()(T&& initial, Ts&&... values) const {
        return impl(
            std::forward<T>(initial),
            std::make_tuple(Wrapper<Ts>(oper, std::forward<Ts>(values))...),
            std::make_index_sequence<sizeof...(Ts)>{});
    }

    template <typename T, typename TupleT, size_t... Idx>
    constexpr auto impl(
        T&& initial, 
        TupleT&& tuple,
        std::index_sequence<Idx...>) const 
    {
        return (std::forward<T>(initial) + ... + std::get<Idx>(tuple));
    }
};

template <typename F>
constexpr auto fold(F&& binary) {
    return Fold<F>(std::forward<F>(binary));
}

template <typename T, typename U>
constexpr auto min(const T& a, const U& b) -> std::common_type_t<T, U> {
    return a < b ? a : b;
}

constexpr int add(int a, int b) {
    return a + b;
}

int main() {
    std::cout << fold(min<int, int>)(1, 3, 2, 5, 4) << std::endl;
    std::cout << fold(min<std::string, std::string>)("abc", "zef", "qwe")
              << std::endl;

    constexpr int result = fold(add)(1, 2, 3, 4, 5);
    std::cout << result << std::endl;

    return 0;
}
