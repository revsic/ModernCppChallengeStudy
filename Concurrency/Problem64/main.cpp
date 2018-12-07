#include <algorithm>
#include <cassert>
#include <chrono>
#include <iostream>
#include <random>

#include <atomic>
#include <condition_variable>
#include <list>
#include <mutex>
#include <thread>
#include <tuple>

template <size_t Threshold, typename Iter>
struct SortPool {
    size_t num_thread;
    std::unique_ptr<std::thread[]> pool;

    std::atomic<int> works = 0;

    std::mutex mtx;
    std::condition_variable cond;
    std::list<std::tuple<Iter, Iter>> lists;

    SortPool(size_t num_thread) : 
        num_thread(num_thread),
        pool(std::make_unique<std::thread[]>(num_thread))
    {
        for (size_t i = 0; i < num_thread; ++i) {
            pool[i] = std::thread([this]{
                while (true) {
                    auto[begin, end] = GetRange();
                    if (works <= 0) break;

                    auto dist = std::distance(begin, end);
                    if (dist <= Threshold) {
                        if (dist > 1) std::sort(begin, end);
                    }
                    else {
                        works += 2;

                        Iter iter_b = begin;
                        Iter iter_e = end - 1;
                        auto pivot = *(begin + dist / 2);
                    
                        while (iter_b < iter_e) {
                            while (pivot < *iter_e) --iter_e;
                            while (iter_b < iter_e && *iter_b < pivot) ++iter_b;

                            std::swap(*iter_b, *iter_e);
                        }
                        {
                            std::unique_lock lock(mtx);
                            lists.emplace_back(begin, iter_b);
                            lists.emplace_back(iter_b, end);
                        }
                    }
                    --works;
                    cond.notify_all();
                }
            });
        }
    }

    ~SortPool() {
        works = 0;
        cond.notify_all();

        for (size_t i = 0; i < num_thread; ++i) {
            if (pool[i].joinable()) {
                pool[i].join();
            }
        }
    }

    std::tuple<Iter, Iter> GetRange() {
        std::unique_lock lock(mtx);
        cond.wait(lock, [&]{ return works <= 0 || lists.size() > 0; });

        if (works <= 0) {
            return std::tuple<Iter, Iter>();
        }
        
        auto range = std::move(lists.front());
        lists.pop_front();

        cond.notify_all();
        return range;
    }

    void Start(Iter begin, Iter end) {
        ++works;
        lists.emplace_back(begin, end);

        cond.notify_all();
        while (works > 0);
    }
};

template <size_t Threshold, typename Iter>
void par_sort(Iter begin, Iter end) {
    SortPool<Threshold, Iter> pool(std::thread::hardware_concurrency());
    pool.Start(begin, end);
}

constexpr size_t TEST_SIZE = 1000000;
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
    benchmark("par", par_sort<100, int*>);

    return 0;
}
