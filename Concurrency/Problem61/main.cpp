#include <algorithm>
#include <cassert>
#include <chrono>
#include <iostream>
#include <vector>

#include <thread>

template <typename InputIter, typename OutputIter, typename F>
void par_transform(InputIter in_begin, 
                   InputIter in_end, 
                   OutputIter out_begin,
                   F&& unary)
{
    using result_t = 
        std::invoke_result_t<F, typename std::iterator_traits<InputIter>::value_type>;

    size_t num_thread = std::thread::hardware_concurrency();
    auto pool = std::make_unique<std::thread[]>(num_thread);

    size_t partition = std::distance(in_begin, in_end) / num_thread;
    for (size_t i = 0; i < num_thread; ++i) {
        InputIter in_iter = in_begin;
        OutputIter out_iter = out_begin;

        if (i == num_thread - 1) {
            in_begin = in_end;
        } else {
            std::advance(in_begin, partition);
            std::advance(out_begin, partition);
        }

        pool[i] = std::thread([=]{
            std::transform(in_iter, in_begin, out_iter, unary);
            // for (; in_iter != in_begin; ++in_iter, ++out_iter) {
            //     *out_iter = unary(*in_iter);
            // }
        });
    }

    for (size_t i = 0; i < num_thread; ++i) {
        if (pool[i].joinable()) {
            pool[i].join();
        }
    }
}

constexpr size_t TEST_SIZE = 100000000;
int input[TEST_SIZE];
int output[TEST_SIZE];

int main() {
    for (size_t i = 0; i < TEST_SIZE; ++i) {
        input[i] = i;
    }

    auto benchmark = [&](auto name, auto& func) {
        using namespace std::chrono;

        for (size_t i = 0; i < TEST_SIZE; ++i) {
            output[i] = 0;
        }

        auto map_func = [](int n) { return n * 2; };

        auto begin = steady_clock::now();
        func(input, input + TEST_SIZE, output, map_func);
        auto end = steady_clock::now();
    
        std::cout << name << ": " << duration_cast<nanoseconds>(end - begin).count() << '\n';
    
        for (size_t i = 0; i < TEST_SIZE; ++i) {
            assert(output[i] == map_func(i));
        }
    };
    
    benchmark("seq", std::transform<int*, int*, int(*)(int)>);
    benchmark("par", par_transform<int*, int*, int(*)(int)>);

    return 0;
}
