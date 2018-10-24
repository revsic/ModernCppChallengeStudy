#include <gsl/gsl>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <type_traits>

#ifdef __APPLE__
#include <experimental/optional>

template <typename T>
using optional = std::experimental::optional<T>;
inline constexpr auto nullopt = std::experimental::nullopt;
#else
#include <optional>

template <typename T>
using optional = std::optional<T>;
inline constexpr auto nullopt = std::nullopt;
#endif

template <typename T>
struct default_releaser {
    void operator()(T& handle) noexcept { }
};

template <typename T, typename Deleter = default_releaser<T>>
class unique_handler {
public:
    unique_handler() : m_handler(nullopt) {
        // Do Nothing
    }

    template <typename Ts>
    unique_handler(Ts&& handler) : m_handler(std::forward<Ts>(handler)) {
        // Do Nothing
    }

    template <typename Ts, typename Ds>
    unique_handler(Ts&& handler, Ds&& deleter) : 
        m_handler(std::forward<Ts>(handler)), m_deleter(std::forward<Ds>(deleter)) 
    {
        // Do Nothing
    }

    unique_handler(const unique_handler&) = delete;
    unique_handler(unique_handler&& handler) noexcept : 
        m_handler(std::move(handler.m_handler)) 
    {
        handler.m_handler = nullopt;
    }

    ~unique_handler() {
        if (m_handler != nullopt) {
            m_deleter(m_handler.value());
        }
    }

    unique_handler& operator=(const unique_handler&) = delete;
    unique_handler& operator=(unique_handler&& handler) noexcept(std::declval<Deleter>()(std::declval<T>())) 
    {
        m_deleter(m_handler.value());
        m_handler = std::move(handler.m_handler);
        handler.m_handler = nullopt;
    }

    T&& release() {
        T value = std::move(m_handler.value());
        m_handler = nullopt;
        return std::move(value);
    }

    void reset(const T& handler = nullopt) {
        m_deleter(m_handler.value());
        m_handler = handler;
    }

    void reset(T&& handler) {
        m_deleter(m_handler.value());
        m_handler = std::move(handler);
    }

    void swap(unique_handler& other) {
        T handle = std::move(other.m_handler.value());
        other.m_handler = std::move(m_handler);
        m_handler = std::move(handle);
    }

    T& get() & {
        return m_handler.value();
    }

    const T& get() const& {
        return m_handler.value();
    }

    T&& get() && {
        return std::move(m_handler.value());
    }

    Deleter& get_deleter() {
        return m_deleter;
    }

    const Deleter& get_deleter() const {
        return m_deleter;;
    }

    operator bool() {
        return m_handler != nullopt;
    }

private:
    optional<T> m_handler;
    Deleter m_deleter;
};

template <typename T>
unique_handler<T> make_handler(T&& handler) {
    return unique_handler<T>(std::forward<T>(handler));
}

template <typename T, typename D>
unique_handler<T, D> make_handler(T&& handler, D&& deleter) {
    return unique_handler<T, D>(std::forward<T>(handler), std::forward<D>(deleter));
}

int main() {
    auto handler = make_handler<std::FILE*, int(*)(std::FILE*)>(std::fopen("./test.txt", "w"), std::fclose);

    char buffer[] = "Hello World !";
    std::fwrite(buffer, sizeof(char), sizeof(buffer), handler.get());
}