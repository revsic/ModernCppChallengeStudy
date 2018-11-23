#define CATCH_CONFIG_MAIN
#include "CircularBuffer.hpp"
#include "catch2/catch.hpp"

TEST_CASE("Constructor", "[Constructor]") {
    CircularBuffer<int> default_ctor;
    REQUIRE(default_ctor.capacity() == 0);

    CircularBuffer<int> cap_ctor(10);
    REQUIRE(cap_ctor.capacity() == 10);
}

TEST_CASE("CopyConstructor", "[Constructor]") {
    CircularBuffer<int> buffer(10);
    buffer.assign({ 0, 1, 2, 3, 4, 5 });

    CircularBuffer<int> buffer2 = buffer;
    for (int i = 0; i < 6; ++i) {
        REQUIRE(buffer2[i] == i);
    }

    CircularBuffer<int> buffer3 = std::move(buffer);
    for (int i = 0; i < 6; ++i) {
        REQUIRE(buffer3[i] == i);
    }
}

TEST_CASE("Assignment", "[Assignment]") {
    CircularBuffer<int> buffer(10);
    CircularBuffer<int> buffer2(5);
    CircularBuffer<int> buffer3(3);
    buffer.assign({ 0, 1, 2, 3, 4, 5 });

    buffer2 = buffer;
    REQUIRE(buffer2.size() == 6);
    REQUIRE(buffer2.capacity() == 10);
    for (int i = 0; i < 6; ++i) {
        REQUIRE(buffer2[i] == i);
    }

    buffer3 = std::move(buffer);
    REQUIRE(buffer2.size() == 6);
    REQUIRE(buffer2.capacity() == 10);
    for (int i = 0; i < 6; ++i) {
        REQUIRE(buffer3[i] == i);
    }
}

TEST_CASE("CircularBuffer::assign", "[Assignment]") {
    CircularBuffer<std::string> buffer(10);
    buffer.assign(3, "test");
    for (int i = 0; i < 3; ++i) {
        REQUIRE(buffer[i] == "test");
    }

    std::vector<std::string> vec;
    for (int i = 0; i < 3; ++i) {
        vec.emplace_back(std::to_string(i));
    }

    buffer.assign(vec.begin(), vec.end());
    for (int i = 0; i < 3; ++i) {
        REQUIRE(buffer[i] == std::to_string(i));
    }

    buffer.assign({"10", "11", "12"});
    for (int i = 0; i < 3; ++i) {
        REQUIRE(buffer[i] == std::to_string(10 + i));
    }
}

TEST_CASE("CircularBuffer::at", "[Element Access]") {
    CircularBuffer<int> buffer(10);
    for (int i = 0; i < 10; ++i) {
        buffer.emplace_back(i);
        REQUIRE(buffer.at(i) == i);
    }
}

TEST_CASE("CircularBuffer::operator[]", "[Element Access]") {
    CircularBuffer<int> buffer(10);
    for (int i = 0; i < 10; ++i) {
        buffer.emplace_back(i);
        REQUIRE(buffer[i] == i);
    }
}

TEST_CASE("CircularBuffer::front", "[Element Access]") {
    CircularBuffer<int> buffer(10);
    for (int i = 0; i < 10; ++i) {
        buffer.emplace_back(i);
        REQUIRE(buffer.front() == i);
        buffer.pop_front();
    }
}

TEST_CASE("CircularBuffer::back", "[Element Access]") {
    CircularBuffer<int> buffer(10);
    for (int i = 0; i < 10; ++i) {
        buffer.emplace_back(i);
        REQUIRE(buffer.back() == i);
        buffer.pop_back();
    }
}

TEST_CASE("CircularBuffer::{begin, end}", "[Iterator]") {
    CircularBuffer<int> buffer(10);
    for (int i = 0; i < 10; ++i) {
        buffer.emplace_back(i);
    }

    size_t i = 0;
    for (auto iter = buffer.begin(); iter != buffer.end(); ++iter, ++i) {
        REQUIRE(*iter == i);
    }
}

TEST_CASE("CircularBuffer::empty", "[Capacity]") {
    CircularBuffer<int> buffer;
    REQUIRE(buffer.empty());

    CircularBuffer<int> buf(10);

    buf.emplace_back(10);
    REQUIRE(!buf.empty());

    buf.pop_back();
    REQUIRE(buf.empty());
}

TEST_CASE("CircularBuffer::full", "[Capacity]") {
    CircularBuffer<int> buffer;
    REQUIRE(buffer.full());

    CircularBuffer<int> buf(10);
    for (int i = 0; i < 10; ++i) {
        buf.emplace_back(i);
    }

    REQUIRE(buf.full());
}

TEST_CASE("CircularBuffer::size", "[Capacity]") {
    CircularBuffer<int> buffer;
    REQUIRE(buffer.size() == 0);

    CircularBuffer<int> buf(10);
    for (int i = 0; i < 10; ++i) {
        REQUIRE(buf.size() == i);
        buf.emplace_back(i);
    }

    for (int i = 10; i > 0; --i) {
        REQUIRE(buf.size() == i);
        buf.pop_back();
    }
}

TEST_CASE("CircularBuffer::capacity", "[Capacity]") {
    CircularBuffer<int> buffer;
    REQUIRE(buffer.capacity() == 0);

    CircularBuffer<int> buf(10);
    REQUIRE(buf.capacity() == 10);
}

TEST_CASE("CircularBuffer::clear", "[Modifier]") {
    CircularBuffer<int> buffer(10);
    for (int i = 0; i < 5; ++i) {
        buffer.emplace_back(i);
    }

    buffer.clear();
    REQUIRE(buffer.size() == 0);
}

TEST_CASE("CircularBuffer::push_back", "[Modifier]") {
    CircularBuffer<int> buffer(10);
    for (int i = 0; i < 5; ++i) {
        buffer.push_back(i);
        REQUIRE(buffer[i] == i);
    }
}

TEST_CASE("CircularBuffer::emplace_back", "[Modifier]") {
    CircularBuffer<std::string> buffer(10);
    for (int i = 0; i < 5; ++i) {
        char str[6] = "test";
        str[4] = '0' + i;

        buffer.emplace_back(str);
        REQUIRE(buffer[i] == "test" + std::to_string(i));
    }
}

TEST_CASE("CircularBuffer::pop_back", "[Modifier]") {
    CircularBuffer<int> buffer(10);
    for (int i = 0; i < 5; ++i) {
        buffer.emplace_back(i);
    }

    for (int i = 4; i >= 0; --i) {
        REQUIRE(buffer.back() == i);
        buffer.pop_back();
    }
}

TEST_CASE("CircularBuffer::pop_front", "[Modifier]") {
    CircularBuffer<int> buffer(10);
    for (int i = 0; i < 5; ++i) {
        buffer.emplace_back(i);
    }

    for (int i = 0; i < 5; ++i) {
        REQUIRE(buffer.front() == i);
        buffer.pop_front();
    }
}
