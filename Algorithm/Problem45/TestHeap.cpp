#include "Heap.hpp"
#include "catch2/catch.hpp"

TEST_CASE("Heap::Constructor", "[Heap]") {
    Heap<int> heap;
    REQUIRE(heap.empty());

    Heap<int> init_list = { 0, 3, 2, 5, 4, 1 };
    for (size_t i = 0; i < 6; ++i) {
        REQUIRE(init_list.front() == 5 - i);
        init_list.pop();
    }

    init_list.assign({ 0, 3, 2, 5, 4, 1 });
    Heap<int> copy_ctor(init_list);
    for (size_t i = 0; i < 6; ++i) {
        REQUIRE(copy_ctor.front() == 5 - i);
        copy_ctor.pop();
    }

    Heap<int> move_ctor(std::move(init_list));
    for (size_t i = 0; i < 6; ++i) {
        REQUIRE(move_ctor.front() == 5 - i);
        move_ctor.pop();
    }
}

TEST_CASE("Heap::Assignment", "[Heap]") {
    Heap<int> q1;
    Heap<int> q2 = { 0, 3, 2, 5, 4, 1 };
    
    q1 = q2;
    for (size_t i = 0; i < 6; ++i) {
        REQUIRE(q1.front() == 5 - i);
        q1.pop();
    }

    q1 = std::move(q2);
    for (size_t i = 0; i < 6; ++i) {
        REQUIRE(q1.front() == 5 - i);
        q1.pop();
    }
}

TEST_CASE("Heap::assign", "[Heap]") {
    Heap<int> init_list;
    init_list.assign({ 0, 3, 2, 5, 4, 1 });
    for (size_t i = 0; i < 6; ++i) {
        REQUIRE(init_list.front() == 5 - i);
        init_list.pop();
    }
}

TEST_CASE("Heap::emplace", "[Heap]") {
    char const* arr[] = { "0", "1", "2", "3" };
    
    Heap<std::string> heap;
    for (auto elem : arr) {
        heap.emplace(elem);
    }

    for (size_t i = 0; i < 4; ++i) {
        REQUIRE(heap.front() == std::to_string(3 - i));
        heap.pop();
    }
}

TEST_CASE("Heap::push", "[Heap]") {
    std::string arr[10];
    for (size_t i = 0; i < 10; ++i) {
        arr[i] = std::to_string(i);
    }

    Heap<std::string> heap;
    for (auto const& elem : arr) {
        heap.push(elem);
    }

    for (size_t i = 0; i < 10; ++i) {
        REQUIRE(heap.front() == std::to_string(9 - i));
        heap.pop();
    }

    Heap<std::string> q2;
    for (auto& elem : arr) {
        q2.push(std::move(elem));
    }

    for (size_t i = 0; i < 10; ++i) {
        REQUIRE(q2.front() == std::to_string(9 - i));
        q2.pop();
    }
}

TEST_CASE("Heap::pop", "[Heap]") {
    Heap<int> que = { 0, 3, 2, 1, 5, 4 };
    
    for (size_t i = 0; i < 3; ++i) {
        que.pop();
    }

    for (size_t i = 0; i < 3; ++i) {
        REQUIRE(que.front() == 2 - i);
        que.pop();
    }
}

TEST_CASE("Heap::size", "[Heap]") {
    Heap<int> que = { 0, 3, 1, 2, 5, 4 };
    REQUIRE(que.size() == 6);
}

TEST_CASE("Heap::empty", "[Heap]") {
    Heap<int> que;
    REQUIRE(que.empty());

    que.assign({1, 2, 3});
    for (int i = 0; i < 3; ++i) {
        que.pop();
    }

    REQUIRE(que.empty());
}

TEST_CASE("Heap::front", "[Heap]") {
    Heap<int> que = { 0, 3, 1, 2, 5, 4 };

    for (int i = 5; i >= 0; --i) {
        REQUIRE(que.front() == i);
        que.pop();
    }

}
