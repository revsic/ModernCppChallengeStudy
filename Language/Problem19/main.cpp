#include <gsl/gsl>
#include <iostream>
#include <vector>

template <typename C, typename... T>
void push_back(C& container, T&&... items) {
    (container.push_back(std::forward<T>(items)), ...);
}

int main() {
    std::vector<int> v = { 1, 2 };
    push_back(v, 3, 4, 5);

    for (int i : v) {
        std::cout << i << std::endl;
    }
}