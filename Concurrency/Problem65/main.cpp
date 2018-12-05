#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

class SyncLogger {
private:
    std::ostream& os;
    std::mutex mtx;

    struct EndToken {};
    struct Locker {
        SyncLogger& logger;
        Locker(SyncLogger& logger) : logger(logger) {
            // Do Nothing
        }

        template <typename T>
        SyncLogger& operator<<(T&& tag) {
            logger.mtx.lock();
            return (logger << std::forward<T>(tag));
        }
    };

public:
    static constexpr EndToken endl = EndToken {};
    Locker lock;

    SyncLogger(std::ostream& os = std::cout) : os(os), lock(*this) {
        // Do Nothing
    }

    template <typename T>
    SyncLogger& operator<<(T&& tag) {
        os << std::forward<T>(tag);
        return *this;
    }

    SyncLogger& operator<<(EndToken const& tag) {
        os << '\n';
        mtx.unlock();
        return *this;
    }
};

namespace sync {
    auto logger = SyncLogger();
    auto cout = logger.lock;
    constexpr auto endl = SyncLogger::endl;
}

int main() {
    size_t num_thread = std::thread::hardware_concurrency();

    std::vector<std::thread> vec;
    vec.reserve(num_thread);

    for(size_t i = 0; i < num_thread; ++i) {
        vec.emplace_back([&, i]{
            for (size_t j = 0; j < 10; ++j) {
                sync::cout << "thread " << i << " : " << j << sync::endl;
            }
        });
    }

    for (size_t i = 0; i < num_thread; ++i) {
        vec[i].join();
    }
    return 0;
}