#include <iostream>
#include <type_traits>
#include <vector>

template <typename T, typename F>
struct MapIter {
    T range;
    F func;

    template <typename IterT>
    struct Iterator {
        IterT iter;
        F& func;

        Iterator(IterT&& iter, F& func) : 
            iter(std::forward<IterT>(iter)), func(func) 
        {
            // Do Nothing
        }

        Iterator& operator++() {
            ++iter;
            return *this;
        }

        auto operator*() {
            return func(*iter);
        }

        bool operator!=(Iterator const& other) {
            return iter != other.iter;
        }
    };

    using value_type = std::invoke_result_t<F, typename std::decay_t<T>::reference>;

    using reference = value_type&;
    using const_reference = value_type const&;

    using iterator = Iterator<typename std::decay_t<T>::iterator>;
    using const_iterator = Iterator<typename std::decay_t<T>::const_iterator>;

    MapIter(T&& range, F&& func) : 
        range(std::forward<T>(range)), func(std::forward<F>(func)) 
    {
        // Do Nothing
    }

    iterator begin() {
        return iterator(range.begin(), func);
    }

    const_iterator begin() const {
        return const_iterator(range.cbegin(), func);
    }

    iterator end() {
        return iterator(range.end(), func);   
    }

    const_iterator end() const {
        return const_iterator(range.cend(), func);
    }
};

template <typename T, typename F>
auto map(T&& cont, F&& func) {
    return MapIter<T, F>(std::forward<T>(cont), std::forward<F>(func));
}

template <typename T, typename F>
auto select(T&& cont, F&& func) {
    return map(std::forward<T>(cont), std::forward<F>(func));
}

struct book {
      int         id;
      std::string title;
      std::string author;
};

int main() {
   std::vector<book> books = {
      { 101, "The C++ Programming Language", "Bjarne Stroustrup" },
      { 203, "Effective Modern C++", "Scott Meyers" },
      { 404, "The Modern C++ Programming Cookbook", "Marius Bancila" }
    };

   auto titles = select(books, [](book const & b) { return b.title; });
   for (auto const& title : titles) {
       std::cout << title << '\n';
   }
   std::cout << std::endl;
}