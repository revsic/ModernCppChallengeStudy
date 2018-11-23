#include "PriorityQueue.hpp"

#include <iostream>
#include <random>

int main(int argc, char* argv[])
{
    constexpr size_t size = 10;
    int arr[size] = { 0, };
    for (size_t i = 0; i < size; ++i) {
        arr[i] = static_cast<int>(i);
    }

    std::random_device rd;
    std::default_random_engine gen(rd());
    std::shuffle(arr, arr + size, gen);

    std::cout << "rand ";
    for (auto i : arr) {
        std::cout << i << ' ';
    }
    std::cout << std::endl;

    PriorityQueue<int> queue;
    for (auto i : arr) {
        queue.emplace(i);
    }

    std::cout << "pque ";
    for (auto i : queue) {
        std::cout << i << ' ';
    }
    std::cout << std::endl;

    std::cout << "size " << queue.size() << std::endl;

    queue.pop();
    std::cout << "pop + top " << queue.top() << std::endl;

    return 0;
}
