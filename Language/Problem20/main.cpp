#include <gsl/gsl>
#include <array>
#include <iostream>
#include <list>
#include <vector>

template <typename C, typename T>
bool contains(C&& cont, T&& item) {
    return std::find(cont.begin(), cont.end(), item) != cont.end();
}

template <typename C, typename T>
bool contains_any(C&& cont, T&& item) {
    return contains(std::forward<C>(cont), std::forward<T>(item));
}

template <typename C, typename T, typename... Ts>
bool contains_any(C&& cont, T&& item, Ts&&... items) {
    return contains(cont, std::forward<T>(item)) 
        || contains_any(std::forward<C>(cont), std::forward<Ts>(items)...);
}

template <typename C, typename T>
bool contains_all(C&& cont, T&& item) {
    return contains(std::forward<C>(cont), std::forward<T>(item));
}

template <typename C, typename T, typename... Ts>
bool contains_all(C&& cont, T&& item, Ts&&... items) {
    return contains(cont, std::forward<T>(item))
        && contains_all(std::forward<C>(cont), std::forward<Ts>(items)...);
}

template <typename C, typename... T>
bool contains_none(C&& cont, T&&... items) {
    return !contains_any(std::forward<C>(cont), std::forward<T>(items)...);
}

int main() {
    std::vector<int> v = { 1, 2, 3, 4, 5 };
    assert(contains_any(v, 0, 3, 30));

    std::array<int, 5> a = { 1, 2, 3, 4, 5 };
    assert(contains_all(a, 1, 3, 5));

    std::list<int> l = { 1, 2, 3, 4, 5 };
    assert(!contains_none(l, 1, 0, 6));
}