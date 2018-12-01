#ifndef HEAP_HPP
#define HEAP_HPP

#include <vector>
#include <iostream>
template <typename T>
class Heap {
public:
    using value_type = T;
    using size_type = typename std::vector<T>::size_type;

    using reference = T&;
    using const_reference = T const&;

    Heap() : m_vec(1) {
        // Do Nothing
    }

    Heap(std::initializer_list<T>&& list) : Heap() {
        for (auto const& elem : list) {
            push(elem);
        }
    }

    Heap(Heap const& heap) : m_vec(heap.m_vec) {
        // Do Nothing
    }

    Heap(Heap&& heap) : m_vec(std::move(heap.m_vec)) {
        // Do Nothing
    }

    Heap& operator=(Heap const& heap) {
        m_vec = heap.m_vec;
        return *this;
    }

    Heap& operator=(Heap&& heap) {
        m_vec = std::move(heap.m_vec);
        return *this;
    }

    void assign(std::initializer_list<T>&& list) {
        m_vec.clear();
        m_vec.emplace_back();

        for (auto const& elem : list) {
            push(elem);
        }
    }

    reference front() {
        return m_vec[1];
    }

    const_reference front() const {
        return m_vec[1];
    }

    bool empty() const {
        return m_vec.size() == 1;
    }

    size_type size() const {
        return m_vec.size() - 1;
    }

    template <typename... U>
    void emplace(U&&... args) {
        m_vec.emplace_back(std::forward<U>(args)...);
        BackwardProp(m_vec.size() - 1);
    }

    void push(T&& elem) {
        m_vec.push_back(std::move(elem));
        BackwardProp(m_vec.size() - 1);
    }

    void push(T const& elem) {
        m_vec.push_back(elem);
        BackwardProp(m_vec.size() - 1);
    }

    void pop() {
        if (m_vec.size() > 1) {
            std::swap(m_vec[1], m_vec.back());
            m_vec.pop_back();
            ForwardProp(1);
        }
    }

    void ForwardProp(size_t idx) {
        size_t left = idx * 2;
        size_t right = idx * 2 + 1;
        if (right < m_vec.size()) {
            if (m_vec[idx] < m_vec[left] || m_vec[idx] < m_vec[right]) {
                if (m_vec[left] < m_vec[right]) {
                    std::swap(m_vec[idx], m_vec[right]);
                    ForwardProp(right);
                }
                else {
                    std::swap(m_vec[idx], m_vec[left]);
                    ForwardProp(left);
                }
            }
        }
        else if (left < m_vec.size()) {
            if (m_vec[idx] < m_vec[left]) {
                std::swap(m_vec[idx], m_vec[left]);
                ForwardProp(left);
            }
        }
    }

    void BackwardProp(size_t idx) {
        if(idx > 1) {
            size_t parent = idx / 2;
            if (m_vec[parent] < m_vec[idx]) {
                std::swap(m_vec[parent], m_vec[idx]);
                BackwardProp(parent);
            }
        }
    }

private:
    std::vector<T> m_vec;
};

#endif