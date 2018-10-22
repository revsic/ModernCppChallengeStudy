#include <gsl/gsl>
#include <iostream>
#include <memory>

template <typename T, size_t ROW, size_t COL>
class Array2D {
public:
    Array2D() : 
        m_array(std::make_unique<T*[]>(ROW)), m_storage(std::make_unique<T[]>(ROW * COL)) 
    {
        for (size_t i = 0; i < ROW; ++i) {
            m_array[i] = &m_storage[i * COL];
        }
    }

    Array2D(std::initializer_list<T>&& list) : Array2D() {
        T* ptr = m_storage.get();
        size_t list_size = list.size();

        if (list_size < ROW * COL) {
            for (size_t i = list_size; i < ROW * COL; ++i) {
                ptr[i] = T();
            }
        }
        else {
            list_size = ROW * COL;
        }

        for (auto iter = list.begin(); list_size; --list_size) {
            if constexpr (T t; noexcept(t = std::move(std::declval<T>()))) {
                *ptr++ = std::move(*iter++);
            }
            else {
                *ptr++ = *iter++;
            }
        }
    }

    Array2D(std::initializer_list<std::initializer_list<T>>&& list) : Array2D() {
        size_t list_size = list.size();
        if (list_size < ROW) {
            for (size_t i = list_size * ROW; i < COL * ROW; ++i) {
                m_storage[i] = T();
            }
        }
        else {
            list_size = ROW;
        }

        auto iter = list.begin();
        for (size_t i = 0; i < list_size; ++i) {
            auto& row = *iter++;
            
            T* ptr = m_array[i];
            size_t row_size = row.size();
            if (row_size < COL) {
                for (size_t j = row_size; j < COL; ++j) {
                    ptr[j] = T();
                }
            }
            else {
                row_size = COL;
            }

            for (auto row_iter = row.begin(); row_size; --row_size) {
                if constexpr (T t; noexcept(t = std::move(std::declval<T>()))) {
                    *ptr++ = std::move(*row_iter++);
                }
                else {
                    *ptr++ = *row_iter++;
                }
            }
        }
    }

    Array2D(const Array2D& other) : Array2D() {
        T* ptr = m_storage.get();
        T* other_storage = other.m_storage.get();
        for (size_t i = 0; i < ROW * COL; ++i) {
            *ptr++ = *other_storage++;
        }
    }

    Array2D(Array2D&& other) : 
        m_array(std::move(other.m_array)), m_storage(std::move(other.m_storage)) 
    {
        // Do Nothinig
    }

    Array2D& operator=(const Array2D& other) {
        T* ptr = m_storage.get();
        T* other_storage = other.m_storage.get();
        
        for (size_t i = 0; i < ROW * COL; ++i) {
            *ptr++ = *other_storage++;
        }
        return *this;
    }

    Array2D& operator=(Array2D&& other) {
        m_array = std::move(other.m_array);
        m_storage = std::move(other.m_storage);
        return *this;
    }

    int* operator[](size_t size) {
        return m_array[size];
    }

    int& at(size_t row, size_t col) {
        return m_array[row][col];
    }

    int* data() {
        return m_storage.get();
    }

    int capacity() const {
        return ROW * COL;
    }

    int* begin() {
        return m_storage.get();
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
    std::unique_ptr<T*[]> m_array;
    std::unique_ptr<T[]> m_storage;
};

int main() {
    constexpr size_t row = 2;
    constexpr size_t col = 3;

    std::cout << "Array1 : " << std::endl;
    Array2D<int, row, col> array1 = { 1, 2, 3, 4, 5, 6 };
    for (size_t i = 0; i < row; ++i) {
        for (size_t j = 0; j < col; ++j) {
            std::cout << array1[i][j] << ' ';
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

    std::cout << "\nArray1 : ";
    for (auto elem : array1) {
        std::cout << elem << ' ';
    }
    std::cout << std::endl;

    std::cout << "\nSwapped Array1 : " << std::endl;
    swap(array1, array2);
    for (size_t i = 0; i < row; ++i) {
        for (size_t j = 0; j < col; ++j) {
            std::cout << array1.at(i, j) << ' ';
        }
        std::cout << std::endl;
    }

    std::cout << "\nArray3 : " << std::endl;
    Array2D<int, 3, 3> array3 = { { 1, 1, 1 }, { 2, 2 } };
    for (size_t i = 0; i < 3; ++i) {
        for (size_t j = 0; j < 3; ++j) {
            std::cout << array3[i][j] << ' ';
        }
        std::cout << std::endl;
    }

    return 0;
}
