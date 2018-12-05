#include <algorithm>
#include <cassert>
#include <chrono>
#include <iostream>
#include <random>

#include <future>

template <typename Iter>
void par_sort(Iter begin, Iter end) {

}

constexpr size_t TEST_SIZE = 100000000;
int input[TEST_SIZE];

int main() {
    auto benchmark = [&](auto name, auto& func) {
        using namespace std::chrono;

        for (size_t i = 0; i < TEST_SIZE; ++i) {
            input[i] = i;
        }
        
        std::random_device rd;
        std::default_random_engine gen(rd());
        std::shuffle(input, input + TEST_SIZE, gen);
        
        auto begin = steady_clock::now();
        func(input, input + TEST_SIZE);
        auto end = steady_clock::now();
    
        std::cout << name << ": " << duration_cast<nanoseconds>(end - begin).count() << '\n';
        
        for (size_t i = 0; i < TEST_SIZE - 1; ++i) {
            assert(input[i] < input[i + 1]);
        }
    };
    
    benchmark("seq", std::sort<int*>);
    benchmark("par", par_sort<int*>);

    return 0;
}
