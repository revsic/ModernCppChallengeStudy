#define CATCH_CONFIG_MAIN
#include "PriorityQueue.hpp"
#include "catch2/catch.hpp"

TEST_CASE("Constructor", "[Constructor]") {
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

TEST_CASE("Assignment", "[Assignment]") {
    PriorityQueue<int> q1;
    PriorityQueue<int> q2 = { 0, 3, 2, 5, 4, 1 };
    
    q1 = q2;
    for (size_t i = 0; i < 6; ++i) {
        REQUIRE(q1[i] == 5 - i);
    }

    q1 = std::move(q2);
    for (size_t i = 0; i < 6; ++i) {
        REQUIRE(q1[i] == 5 - i);
    }
}

TEST_CASE("PriorityQueue::emplace", "[Modifier]") {
    char const* arr[] = { "0", "1", "2", "3" };
    
    PriorityQueue<std::string> que;
    for (auto elem : arr) {
        que.emplace(elem);
    }

    for (size_t i = 0; i < 4; ++i) {
        REQUIRE(que[i] == std::to_string(3 - i));
    }
}

TEST_CASE("PriorityQueue::push", "[Modifier]") {
    std::string arr[10];
    for (size_t i = 0; i < 10; ++i) {
        arr[i] = std::to_string(i);
    }

    PriorityQueue<std::string> q1;
    for (auto const& elem : arr) {
        q1.push(elem);
    }

    for (size_t i = 0; i < 10; ++i) {
        REQUIRE(q1[i] == std::to_string(9 - i));
    }

    PriorityQueue<std::string> q2;
    for (auto& elem : arr) {
        q2.push(std::move(elem));
    }

    for (size_t i = 0; i < 10; ++i) {
        REQUIRE(q2[i] == std::to_string(9 - i));
    }
}

TEST_CASE("PriorityQueue::pop", "[Modifier]") {
    PriorityQueue<int> que = { 0, 3, 2, 1, 5, 4 };
    
    for (size_t i = 0; i < 3; ++i) {
        que.pop();
    }

    for (size_t i = 0; i < 3; ++i) {
        REQUIRE(que[i] == 2 - i);
    }
}

TEST_CASE("PriorityQueue::{begin, end}", "[Iterator]") {
    PriorityQueue<int> que = { 0, 3, 1, 2, 5, 4 };
    
    static_assert(!std::is_const_v<
        std::remove_reference_t<
            std::iterator_traits<PriorityQueue<int>::iterator>::reference>>);
    static_assert(std::is_const_v<
        std::remove_reference_t<
            std::iterator_traits<PriorityQueue<int>::const_iterator>::reference>>);

    size_t i = 5; 
    for (auto iter = que.begin(); iter != que.end(); ++iter, --i) {
        REQUIRE(*iter == i);
    }

    i = 5;
    for (auto iter = que.cbegin(); iter != que.cend(); ++iter, --i) {
        REQUIRE(*iter == i);
    }
}

TEST_CASE("PriorityQueue::size", "[Capacity]") {
    PriorityQueue<int> que = { 0, 3, 1, 2, 5, 4 };
    REQUIRE(que.size() == 6);
}

TEST_CASE("PriorityQueue::top", "[Element Access]") {
    PriorityQueue<int> que = { 0, 3, 1, 2, 5, 4 };

    for (int i = 5; i >= 0; --i) {
        REQUIRE(que.top() == i);
        que.pop();
    }

}
TEST_CASE("PriorityQueue::operator[]", "[Element Access]") {
    PriorityQueue<int> que = { 0, 3, 1, 2, 5, 4 };
    for (size_t i = 0; i < 6; ++i) {
        REQUIRE(que[i] == 5 - i);
    }
}