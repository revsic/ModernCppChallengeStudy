#include <gsl/gsl>
#include <iostream>
#include <utility>

template <typename T>
auto minimum(T&& arg) {
    return std::forward<T>(arg);
}

template <typename T, typename... U>
auto minimum(T&& given, U&&... args) -> std::common_type_t<T, U...> {
    auto min = minimum(std::forward<U>(args)...);
    if (given < min) {
        return std::forward<T>(given);
    }
    else {
        return min;
    }
}

template <typename... T>
auto minimum(T&&... args) -> std::common_type_t<T...> {
    return minimum(std::forward<T>(args)...);   
}

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

        template <typename Ts>
        constexpr auto operator+(Ts&& other) const {
            return oper(value, other);
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

    template <typename T, typename Ts, size_t... Idx>
    constexpr auto impl(
        T&& initial, 
        Ts&& tuple,
        std::index_sequence<Idx...>) const 
    {
        constexpr size_t max = sizeof...(Idx) - 1;
        return (std::get<max - Idx>(tuple) + ... + std::forward<T>(initial));
    }
};

template <typename F>
constexpr auto fold(F&& binary) {
    return Fold<F>(std::forward<F>(binary));
}

constexpr int add(int a, int b) {
    return a + b;
}

int main() {
    std::cout << minimum(1, 3, 2, 5, 4) << std::endl;
    std::cout << minimum(
                    std::string("abc"), 
                    std::string("123"), 
                    std::string("zef")) 
              << std::endl;
    
    constexpr int result = fold(add)(1, 2, 3, 4, 5);
    std::cout << result << std::endl;

    return 0;
}
