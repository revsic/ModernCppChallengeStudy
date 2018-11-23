#define CATCH_CONFIG_MAIN
#include "PriorityQueue.hpp"
#include "catch2/catch.hpp"

#include <random>

static std::random_device rd;
static std::default_random_engine gen(rd());

TEST_CASE("Constructor", "[Initialize]") {
    PriorityQueue<int> queue;
    REQUIRE(queue.empty());

    PriorityQueue<int> queue_list = { 0, 3, 2, 5, 4, 1 };
    for (size_t i = 0; i < 6; ++i) {
        REQUIRE(queue_list[i] == 5 - i);
    }

    PriorityQueue<int> copy_ctor(queue_list);
    for (size_t i = 0; i < 6; ++i) {
        REQUIRE(copy_ctor[i] == 5 - i);
    }

    PriorityQueue<int> move_ctor(std::move(queue_list));
    for (size_t i = 0; i < 6; ++i) {
        REQUIRE(move_ctor[i] == 5 - i);
    }
}

TEST_CASE("Assignment", "[Initialize]") {

}

TEST_CASE("Push, Emplace", "[Modification]") {

}

TEST_CASE("Pop", "[Modification]") {

}

TEST_CASE("Iterating", "[Iterator]") {

}

TEST_CASE("Size", "[Get Value]") {

}

TEST_CASE("Top", "[Get Value]") {

}
