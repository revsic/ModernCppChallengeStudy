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

template <typename T, typename Releaser = default_releaser<T>>
class unique_handler {
public:
    unique_handler() : m_handler(nullopt) {
        // Do Nothing
    }

    unique_handler(const T& handler) : m_handler(handler) {
        // Do Nothing
    }

    unique_handler(T&& handler) : m_handler(std::move(handler)) {
        // Do Nothing
    }

    template <typename Ts, typename Rs>
    unique_handler(Ts&& handler, Rs&& releaser) : 
        m_handler(std::forward<Ts>(handler)), m_releaser(std::forward<Rs>(releaser)) 
    {
        // Do Nothing
    }

    unique_handler(const unique_handler&) = delete;
    unique_handler(unique_handler&& handler) noexcept : 
        m_handler(std::move(handler.m_handler)), m_releaser(std::move(handler.m_releaser))
    {
        handler.m_handler = nullopt;
    }

    ~unique_handler() {
        reset();
    }

    unique_handler& operator=(const unique_handler&) = delete;
    unique_handler& operator=(unique_handler&& handler) noexcept(
        noexcept(std::declval<Releaser>()(std::declval<T>())))
    {
        reset();
        m_handler = std::move(handler.release());
        return *this;
    }

    optional<T>&& release() {
        optional<T> value;
        if (m_handler) {
            value = std::move(m_handler);
            m_handler = nullopt;
        }
        return std::move(value);
    }

    void reset() {
        if (m_handler) {
            m_releaser(m_handler.value());
            m_handler = nullopt;
        }
    }

    void reset(const T& handler) {
        if (m_handler) {
            m_releaser(m_handler.value());
        }
        m_handler = handler;
    }

    void reset(T&& handler) {
        if (m_handler) {
            m_releaser(m_handler.value());
        }
        m_handler = std::move(handler);
    }

    void swap(unique_handler& other) {
        std::swap(m_handler, other.m_handler);
        std::swap(m_releaser, other.m_releaser);
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

    Releaser& get_releaser() & {
        return m_releaser;
    }

    const Releaser& get_releaser() const& {
        return m_releaser;
    }

    Releaser&& get_releaser() && {
        return std::move(m_releaser);
    }

    operator bool() {
        return m_handler != nullopt;
    }

private:
    optional<T> m_handler;
    Releaser m_releaser;
};


template <typename T, typename R = default_releaser<T>>
unique_handler<T, R> make_handler(const T& handler, R&& releaser = default_releaser<T>{}) {
    return unique_handler<T, R>(handler, std::forward<R>(releaser));
}
template <typename T, typename R = default_releaser<T>>
unique_handler<T, R> make_handler(T&& handler, R&& releaser = default_releaser<T>{}) {
    return unique_handler<T, R>(std::forward<T>(handler), std::forward<R>(releaser));
}


int main() {
    auto handler = make_handler<std::FILE*>(std::fopen("./test.txt", "w"), std::fclose);
    char buffer[] = "Hello World !";
    std::fwrite(buffer, 1, sizeof(buffer), handler.get().value());

    handler = make_handler<std::FILE*>(std::fopen("./test.txt", "r"), std::fclose);
    std::fread(buffer, 1, sizeof(buffer), handler.get().value());

    auto raw_opt = handler.release();
    handler = make_handler<std::FILE*>(raw_opt.value(), std::fclose);

    std::cout << buffer << std::endl;
    return 0;
}
