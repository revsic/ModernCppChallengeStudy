#include <gsl/gsl>
#include <chrono>
#include <iostream>
#include <thread>

using namespace std::literals;

template <typename T, typename F, typename... Args>
auto performance(F&& func, Args&&... args) {
    auto start = std::chrono::steady_clock::now();
    func(std::forward<Args>(args)...);
    auto end = std::chrono::steady_clock::now();
    return std::chrono::duration_cast<T>(end - start);
}

int main(int argc, char* argv[])
{
    auto res = performance<std::chrono::milliseconds>([](auto n) {
        std::this_thread::sleep_for(n);
    }, 100ms);

    std::cout << res.count() << "ms" << std::endl;

    return 0;
}
