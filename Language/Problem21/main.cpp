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
        m_handler(std::move(handler.m_handler)), m_deleter(std::move(handler.m_deleter))
    {
        handler.m_handler = nullopt;
    }

    ~unique_handler() {
        if (m_handler) {
            m_deleter(m_handler.value());
        }
    }

    unique_handler& operator=(const unique_handler&) = delete;
    unique_handler& operator=(unique_handler&& handler) noexcept(noexcept(std::declval<Deleter>()(std::declval<T>())))
    {
        if (m_handler) {
            m_deleter(m_handler.value());
        }
        m_handler = std::move(handler.m_handler);
        handler.m_handler = nullopt;
        return *this;
    }

    optional<T> release() {
        optional<T> value;
        if (m_handler) {
            value = m_handler;
            m_handler = nullopt;
        }
        return value;
    }

    void reset() {
        if (m_handler) {
            m_deleter(m_handler.value());
            m_handler = nullopt;
        }
    }

    void reset(const T& handler) {
        if (m_handler) {
            m_deleter(m_handler.value());
        }
        m_handler = handler;
    }

    void reset(T&& handler) {
        if (m_handler) {
            m_deleter(m_handler.value());
        }
        m_handler = std::move(handler);
    }

    void swap(unique_handler& other) {
        optional<T> handle = std::move(other.m_handler);
        other.m_handler = std::move(m_handler);
        m_handler = std::move(handle);
    }

    optional<T>& get() & {
        return m_handler;
    }

    const optional<T>& get() const& {
        return m_handler;
    }

    optional<T>&& get() && {
        return std::move(m_handler);
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
    auto handler = make_handler<std::FILE*>(std::fopen("./test.txt", "w"), std::fclose);
    char buffer[] = "Hello World !";
    std::fwrite(buffer, 1, sizeof(buffer), handler.get().value());

    assert(bool(handler));
    handler.reset();
    assert(!bool(handler));
    
    handler = make_handler<std::FILE*>(std::fopen("./test.txt", "r"), std::fclose);
    std::FILE* raw_handler = handler.release().value();
    std::fread(buffer, 1, sizeof(buffer), raw_handler);

    std::cout << buffer << std::endl;
    return 0;
}