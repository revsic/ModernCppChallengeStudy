#include <algorithm>
#include <iostream>

#include <functional>
#include <random>
#include <vector>

template <typename T, typename Allocator = std::allocator<T>>
class PriorityQueue {
public:
    using value_type = T;
    using allocator_type = Allocator;

    using reference = value_type&;
    using const_reference = value_type const&;

    using iterator = decltype(std::declval<std::vector<int>>().begin());
    using const_iterator = iterator const;

    PriorityQueue() {
        // Do Nothing
    }

    PriorityQueue(std::initializer_list<T>&& init) : 
        m_vec(std::move(init)) 
    {
        std::sort(m_vec.begin(), m_vec.end(), std::greater<T>());
    }

    PriorityQueue(PriorityQueue const& queue) : 
        m_vec(queue.m_vec) 
    {
        // Do Nothing
    }

    PriorityQueue(PriorityQueue&& queue) :
        m_vec(std::move(queue.m_vec))
    {
        // Do Nothing
    }

    PriorityQueue& operator=(PriorityQueue const& queue) {
        m_vec = queue.m_vec;
    }

    PriorityQueue& operator=(PriorityQueue&& queue) {
        m_vec = std::move(queue.m_vec);
    }

    reference top() {
        return m_vec.front();
    }

    const_reference top() const {
        return m_vec.front();
    }

    size_t size() const {
        return m_vec.size();
    }

    bool empty() const {
        return m_vec.empty();
    }

    void push(T const& elem) {
        size_t begin = 0;
        size_t end = m_vec.size();

        while (begin < end) {
            size_t mid = (begin + end) / 2;
            if (elem > m_vec[mid]) {
                end = mid;
            }
            else {
                begin = mid + 1;
            }
        }
        m_vec.emplace(m_vec.begin() + begin, elem);
    }
    
    template <typename... U>
    void emplace(U&&... args) {
        push(T(std::forward<U>(args)...));
    }

    void pop() {
        m_vec.erase(m_vec.begin());
    }

    void swap(PriorityQueue& queue) {
        std::swap(m_vec, queue.m_vec);
    }

    iterator begin() {
        return m_vec.begin();
    }

    const_iterator begin() const {
        return m_vec.begin();
    }

    const_iterator cbegin() const {
        return m_vec.cbegin();
    }

    iterator end() {
        return m_vec.end();
    }

    const_iterator end() const {
        return m_vec.end();
    }

    const_iterator cend() const {
        return m_vec.cend();
    }

private:
    std::vector<value_type, allocator_type> m_vec;
};

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
