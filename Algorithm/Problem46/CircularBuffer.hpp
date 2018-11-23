#ifndef CIRCULAR_BUFFER_HPP
#define CIRCULAR_BUFFER_HPP

#include <memory>
#include <stdexcept>
#include <type_traits>

template <typename T,
          typename = std::enable_if_t<std::is_default_constructible_v<T>>>
class CircularBuffer {
public:
    template <typename U>
    class Iterator {
    public:
        Iterator(U* ptr, size_t pos, size_t size_buffer) :
            ptr(ptr), pos(pos), size_buffer(size_buffer)
        {
            // Do Nothing
        }

        Iterator& operator++() {
            pos = (pos + 1) % size_buffer;
            return *this;
        }

        bool operator!=(Iterator const& iter) const {
            return pos != iter.pos;
        }

        U& operator*() const {
            return ptr[pos];
        }

    private:
        U* ptr;
        size_t pos;
        size_t size_buffer;
    };

    using value_type = T;

    using reference = value_type&;
    using const_reference = value_type const&;

    using iterator = Iterator<value_type>;
    using const_iterator = Iterator<value_type const>;

    CircularBuffer() : 
        size_buffer(1), 
        buffer(nullptr) 
    {
        // Do Nothing
    }

    CircularBuffer(size_t capacity) :
        size_buffer(capacity + 1), 
        buffer(std::make_unique<value_type[]>(size_buffer))
    {
        // Do Nothing
    }

    CircularBuffer(CircularBuffer const& cbuffer) : 
        size_buffer(cbuffer.size_buffer),
        buffer(std::make_unique<T[]>(size_buffer)),
        num_data(cbuffer.num_data),
        ptr_head(0),
        ptr_tail(num_data)
    {
        for (size_t i = 0; i < num_data; ++i) {
            buffer[i] = cbuffer[i];
        }
    }

    CircularBuffer(CircularBuffer&& cbuffer) : 
        size_buffer(cbuffer.size_buffer), 
        buffer(std::move(cbuffer.buffer)),
        num_data(cbuffer.num_data),
        ptr_head(cbuffer.ptr_head),
        ptr_tail(cbuffer.ptr_tail)
    {
        // Do Nothing
    }

    CircularBuffer& operator=(CircularBuffer const& cbuffer) {
        size_buffer = cbuffer.size_buffer;
        buffer = std::make_unique<T[]>(size_buffer);

        ptr_head = 0;
        ptr_tail = 0;
        num_data = cbuffer.num_data;
        for (size_t i = 0; i < num_data; ++i) {
            buffer[i] = cbuffer[i];
        }

        return *this;
    }

    CircularBuffer& operator=(CircularBuffer&& cbuffer) {
        size_buffer = cbuffer.size_buffer;
        buffer = std::move(cbuffer.buffer);
        num_data = cbuffer.num_data;
        ptr_head = cbuffer.ptr_head;
        ptr_tail = cbuffer.ptr_tail;
        return *this;
    }

    void assign(size_t count, T const& elem) {
        clear();
        count = std::min(capacity(), count);
        while (count--) {
            push_back(elem);
        }
    }

    template <typename InputIt>
    void assign(InputIt first, InputIt last) {
        clear();
        size_t max_cap = capacity();
        for (; max_cap && first != last; ++first, --max_cap) {
            push_back(*first);
        }
    }

    void assign(std::initializer_list<T>&& list) {
        assign(list.begin(), list.end());
    }

    reference at(size_t pos) {
        if (pos < num_data) {
            pos = (ptr_head + pos) % size_buffer;
            return buffer[pos];
        }
        throw std::out_of_range("CircularBuffer out_of_range exception occured");
    }

    const_reference at(size_t pos) const {
        if (pos < num_data) {
            pos = (ptr_head + pos) % size_buffer;
            return buffer[pos];
        }
        throw std::out_of_range("CircularBuffer out_of_range exception occured");
    }

    reference operator[](size_t pos) {
        return at(pos);
    }

    const_reference operator[](size_t pos) const {
        return at(pos);
    }

    reference front() {
        return buffer[ptr_head];
    }

    const_reference front() const {
        return buffer[ptr_head];
    }

    reference back() {
        int prev = static_cast<int>(ptr_tail) - 1;
        if (prev < 0) {
            prev = static_cast<int>(size_buffer) - 1;
        }
        return buffer[prev];
    }

    const_reference back() const {
        int prev = static_cast<int>(ptr_tail) - 1;
        if (prev < 0) {
            prev = size_buffer - 1;
        }
        return buffer[prev];
    }

    iterator begin() {
        return iterator(buffer.get(), ptr_head, size_buffer);
    }

    const_iterator begin() const {
        return const_iterator(buffer.get(), ptr_head, size_buffer);
    }

    const_iterator cbegin() const {
        return const_iterator(buffer.get(), ptr_head, size_buffer);
    }

    iterator end() {
        return iterator(buffer.get(), ptr_tail, size_buffer);
    }

    const_iterator end() const {
        return const_iterator(buffer.get(), ptr_tail, size_buffer);
    }

    const_iterator cend() const {
        return const_iterator(buffer.get(), ptr_tail, size_buffer);
    }

    bool empty() const {
        return num_data == 0;
    }

    bool full() const {
        return num_data == capacity();
    }

    size_t size() const {
        return num_data;
    }

    size_t capacity() const {
        return size_buffer - 1;
    }

    void clear() {
        num_data = ptr_head = ptr_tail = 0;
    }

    void push_back(T const& elem) {
        emplace_back(elem);
    }

    void push_back(T&& elem) {
        emplace_back(std::move(elem))
    }

    template <typename... U>
    void emplace_back(U&&... args) {
        buffer[ptr_tail] = T(std::forward<U>(args)...);

        num_data += 1;
        ptr_tail = (ptr_tail + 1) % size_buffer;
    }

    void pop_back() {
        num_data -= 1;
        int prev = static_cast<int>(ptr_tail) - 1;
        if (prev < 0) {
            prev = static_cast<int>(size_buffer) - 1;
        }
        ptr_tail = static_cast<size_t>(prev);
    }

    void pop_front() {
        num_data -= 1;
        ptr_head = (ptr_head + 1) % size_buffer;
    }

private:
    size_t size_buffer;
    std::unique_ptr<T[]> buffer;

    size_t num_data = 0;
    size_t ptr_head = 0;
    size_t ptr_tail = 0;
};

#endif