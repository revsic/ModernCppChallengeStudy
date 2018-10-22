#include <gsl/gsl>
#include <iostream>

template <typename T, size_t ROW, size_t COL>
class Array2D {
public:
    Array2D() : m_array(new T*[ROW]), m_storage(new T[ROW * COL]) {
        for (size_t i = 0; i < ROW; ++i) {
            m_array[i] = &m_storage[i * COL];
        }
    }

    Array2D(std::initializer_list<T>&& list) : Array2D() {
        T t;
        auto begin = list.begin();
        for (size_t i = 0; i < ROW; ++i) {
            for (size_t j = 0; j < COL; ++j) {
                if (begin != list.end()) {
                    if constexpr (noexcept(t = std::move(std::declval<T>()))) {
                        m_array[i][j] = std::move(*begin);
                    }
                    else {
                        m_array[i][j] = *begin;
                    }
                    ++begin;
                }
                else {
                    m_array[i][j] = T();
                }
            }
        }
    }

    Array2D(std::initializer_list<std::initializer_list<T>>&& list) : Array2D() {
        T t;
        auto begin = list.begin();
        for (size_t i = 0; i < ROW; ++i) {
            if (begin != list.end()) {
                auto& iter = *begin;
                auto col_begin = iter.begin();
                for (size_t j = 0; j < COL; ++j) {
                    if (col_begin != iter.end()) {
                        if constexpr (noexcept(t = std::move(std::declval<T>()))) {
                            m_array[i][j] = std::move(*col_begin);
                        }
                        else {
                            m_array[i][j] = *col_begin;
                        }
                        ++col_begin;
                    }
                    else {
                        m_array[i][j] = T();
                    }
                }
                ++begin;
            }
            else {
                for (size_t j = 0; j < COL; ++j) {
                    m_array[i][j] = T();
                }
            }
        }
    }

    ~Array2D() {
        if (m_array != nullptr) {
            delete[] m_array;
        }
        if (m_storage != nullptr) {
            delete[] m_storage;
        }
    }

    Array2D(const Array2D& array) : Array2D() {
        for (size_t i = 0; i < ROW; ++i) {
            for (size_t j = 0; j < COL; ++j) {
                m_array[i][j] = array[i][j];
            }
        }
    }

    Array2D(Array2D&& array) : m_array(array.m_array), m_storage(array.m_storage) {
        array.m_array = nullptr;
        array.m_storage = nullptr;
    }

    Array2D& operator=(const Array2D& array) {
        for (size_t i = 0; i < ROW; ++i) {
            for (size_t j = 0; j < COL; ++j) {
                m_array[i][j] = array[i][j];
            }
        }
        return *this;
    }

    Array2D& operator=(Array2D&& array) {
        delete[] m_array;
        delete[] m_storage;

        m_array = array.m_array;
        m_storage = array.m_storage;

        array.m_array = nullptr;
        array.m_storage = nullptr;

        return *this;
    }

    int* operator[](size_t size) {
        return m_array[size];
    }

    int& at(size_t row, size_t col) {
        return m_array[row][col];
    }

    int* data() {
        return m_storage;
    }

    int capacity() const {
        return ROW * COL;
    }

    int* begin() {
        return m_storage;
    }

    int* end() {
        return &m_storage[ROW * COL];
    }

    friend void swap(Array2D& arr1, Array2D& arr2) {
        Array2D tmp = std::move(arr1);
        arr1 = std::move(arr2);
        arr2 = std::move(tmp);
    }

private:
    T** m_array;
    T* m_storage;
};

int main() {
    constexpr size_t row = 2;
    constexpr size_t col = 3;

    std::cout << "Array1 : " << std::endl;
    Array2D<int, row, col> array = { 1, 2, 3, 4, 5, 6 };
    for (size_t i = 0; i < row; ++i) {
        for (size_t j = 0; j < col; ++j) {
            std::cout << array[i][j] << ' ';
        }
        std::cout << std::endl;
    }
    
    std::cout << "\nArray2 : " << std::endl;
    Array2D<int, row, col> array2 = { { 1, 1 }, { 2 } };
    for (size_t i = 0; i < row; ++i) {
        for (size_t j = 0; j < col; ++j) {
            std::cout << array2[i][j] << ' ';
        }
        std::cout << std::endl;
    }

    std::cout << "\nArray : ";
    for (auto elem : array) {
        std::cout << elem << ' ';
    }
    std::cout << std::endl;

    std::cout << "\nSwapped Array1 : " << std::endl;
    swap(array, array2);
    for (size_t i = 0; i < row; ++i) {
        for (size_t j = 0; j < col; ++j) {
            std::cout << array.at(i, j) << ' ';
        }
        std::cout << std::endl;
    }
    return 0;
}
