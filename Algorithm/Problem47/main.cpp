#define CATCH_CONFIG_MAIN
#include "DoubleBuffer.hpp"
#include "catch2/catch.hpp"

TEST_CASE("Constructor", "[Constructor]") {
    DoubleBuffer<int> default_ctor;

    int n = 10;
    DoubleBuffer<int> copy_ctor(n);
    REQUIRE(copy_ctor.Read() == n);

    DoubleBuffer<std::string> move_ctor("a");
    REQUIRE(move_ctor.Read() == "a");
}

TEST_CASE("CopyConstructor", "[Constructor]") {
    DoubleBuffer<int> buffer(10);
    DoubleBuffer<int> copy_buf(buffer);
    REQUIRE(copy_buf.Read() == 10);

    DoubleBuffer<int> move_buf(std::move(buffer));
    REQUIRE(move_buf.Read() == 10);
}

TEST_CASE("Assignment", "[Assignment]") {
    DoubleBuffer<int> buffer(10);
    DoubleBuffer<int> buffer2(5);
    DoubleBuffer<int> buffer3(3);

    buffer2 = buffer;
    REQUIRE(buffer2.Read() == 10);

    buffer3 = std::move(buffer);
    REQUIRE(buffer3.Read() == 10);
}

