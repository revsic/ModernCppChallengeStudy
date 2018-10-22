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

template <typename F, typename T>
struct Wrapper {
    F oper;
    T value;

    constexpr Wrapper(F&& oper, T&& value) : oper(std::forward<F>(oper)), value(std::forward<T>(value)) {
        // Do nothing
    }

    template <typename U>
    constexpr auto operator+(const Wrapper<F, U>& other) {
        return oper(value, other.value);
    }
};

template <typename F, typename... T>
struct Folder {
    F oper;
    std::tuple<Wrapper<F, T>...> values;

    constexpr Folder(F&& oper, T&&... values) : 
        oper(std::forward<F>(oper)), values(Wrapper<F, T>(oper, std::forward<T>(values))...)
    {
        // DO Nothing
    }

    template <typename U>
    constexpr auto run(U&& initial) {
        return impl(std::forward<U>(initial), std::make_index_sequence<sizeof...(T)>{});
    }

    template <typename U, size_t... Idx>
    constexpr auto impl(U&& initial, std::index_sequence<Idx...>) {
        return (Wrapper<F, U>(std::move(oper), std::forward<U>(initial)) + ... + std::get<Idx>(values));
    }
};

template <typename F, typename T, typename... U>
auto fold(F&& binary, T&& initial, U&&... args) {
    return Folder<F, U...>(std::forward<F>(binary), std::forward<U>(args)...).run(std::forward<T>(initial));
}

int main() {
    std::cout << minimum(1, 3, 2, 5, 4) << std::endl;
    std::cout << minimum(
                    std::string("abc"), 
                    std::string("123"), 
                    std::string("zef")) 
              << std::endl;
    
    std::cout << fold([](int a, int b) { return a + b; }, 1, 2, 3) << std::endl;

    return 0;
}
