#ifndef DOUBLE_BUFFER_HPP
#define DOUBLE_BUFFER_HPP

#include <shared_mutex>

template <typename T>
class DoubleBuffer {
public:
    DoubleBuffer() {
        // Do Nothing
    }

    DoubleBuffer(T const& data) : data(data), old(data) {
        // Do Nothing
    }

    DoubleBuffer(T&& data) : data(std::move(data)), old(data) {
        // Do Nothing
    }

    DoubleBuffer(DoubleBuffer& buffer) : data(buffer.Read()), old(data) {
        // Do Nothing
    }

    DoubleBuffer(DoubleBuffer&& buffer) : data(std::move(buffer.data)), old(data) {
        // Do Nothing
    }

    DoubleBuffer& operator=(DoubleBuffer& buffer) {
        Write(buffer.Read());
        return *this;
    }

    DoubleBuffer& operator=(DoubleBuffer&& buffer) {
        Write(std::move(buffer.data));
        return *this;
    }

    T Read() {
        std::shared_lock lock(mtx, std::try_to_lock);
        if (lock.owns_lock()) {
            return data;
        }
        else {
            return old;
        }
    }

    void Write(T const& input) {
        {
            std::unique_lock lock(mtx);
            data = input;
        }
        old = data;
    }

    void Write(T&& input) {
        {
            std::unique_lock lock(mtx);
            data = std::move(input);
        }
        old = data;
    }

private:
    T data;
    T old;
    std::shared_mutex mtx;
};

#endif