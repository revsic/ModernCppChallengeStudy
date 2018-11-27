#include <algorithm>
#include <iostream>
#include <random>

template <typename Iter>
void qsort_v1(Iter begin, Iter end) {
    using category = typename std::iterator_traits<Iter>::iterator_category;
    using value_type = typename std::iterator_traits<Iter>::value_type;
    static_assert(
        std::is_same_v<category, std::random_access_iterator_tag>, 
        "Iterator should be RandomAccessIterator");

    if (std::distance(begin, end) <= 1) {
        return;
    }

    Iter iter_b = begin;
    Iter iter_e = end - 1;
    value_type pivot = *(begin + std::distance(begin, end) / 2);
 
    while (iter_b < iter_e) {
        while (pivot < *iter_e) --iter_e;
        while (iter_b < iter_e && *iter_b < pivot) ++iter_b;

        std::swap(*iter_b, *iter_e);
    }

    qsort_v1(begin, iter_b);
    qsort_v1(iter_b, end);
}

int main() {
    std::random_device rd;
    std::default_random_engine gen(rd());

    auto display = [](auto& arr) {
        for (int elem : arr) {
            std::cout << elem << ' ';
        }
        std::cout << std::endl;
    };

    constexpr size_t NUM_TEST = 10000;
    for (size_t i = 0; i < NUM_TEST; ++i) {
        int arr[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        std::shuffle(arr, arr + 10, gen);

        qsort_v1(arr, arr + 10);

        bool fail = false;
        for (size_t j = 1; j < 10; ++j) {
            if (arr[j] < arr[j - 1]) {
                fail = true;
                break;
            }
        }

        if (fail) {
            std::cout << "[*] fail : ";
            display(arr);
        }
    }
}