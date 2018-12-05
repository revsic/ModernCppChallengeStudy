#include <algorithm>
#include <cassert>
#include <chrono>
#include <iostream>

#include <thread>

template <typename ForwardIt>
ForwardIt par_max_element(ForwardIt begin, ForwardIt end) {
    size_t num_thread = std::thread::hardware_concurrency();
    size_t partition = std::distance(begin, end) / num_thread;

    auto pool = std::make_unique<std::thread[]>(num_thread);
    auto max_elem = std::make_unique<ForwardIt[]>(num_thread);

    for (size_t i = 0; i < num_thread; ++i) {
        ForwardIt iter = begin;
        if (i == num_thread - 1) {
            begin = end;
        } else {
            std::advance(begin, partition);
        }

        pool[i] = std::thread([=, &max_elem]{
            max_elem[i] = std::max_element(iter, begin);
        });
    }

    for (size_t i = 0; i < num_thread; ++i) {
        if (pool[i].joinable()) {
            pool[i].join();
        }
    }

    return *std::max_element(max_elem.get(), max_elem.get() + num_thread);
}

constexpr size_t TEST_SIZE = 100000000;
int input[TEST_SIZE];

int main() {
    for (size_t i = 0; i < TEST_SIZE; ++i) {
        input[i] = i;
    }

    auto benchmark = [&](auto name, auto& func) {
        using namespace std::chrono;

        auto begin = steady_clock::now();
        auto res = func(input, input + TEST_SIZE);
        auto end = steady_clock::now();
    
        std::cout << name << ": " << duration_cast<nanoseconds>(end - begin).count() << '\n';
        assert(*res == TEST_SIZE - 1);
    };
    
    benchmark("seq", std::max_element<int*>);
    benchmark("par", par_max_element<int*>);

    return 0;
}
