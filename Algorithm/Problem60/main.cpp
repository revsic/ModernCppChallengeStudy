#include <chrono>
#include <iostream>
#include <thread>

using namespace std::literals;

template <size_t H, size_t W>
void simulate(bool (&table)[H][W]) {
    auto n_neighbor = [&](size_t height, size_t width) {
        std::tuple<int, int> delta[] = 
            { { -1, -1 }, { -1, 0 }, { -1, 1 }, { 0, -1 }, { 0, 1 }, { 1, -1 }, { 1, 0 }, { 1, 1 } };
        
        size_t num = 0;
        for (auto[dh, dw] : delta) {
            size_t nh = height + dh;
            size_t nw = width + dw;
            if (nh < H && nw < W) {
                num += static_cast<size_t>(table[nh][nw]);
            }
        }
    
        return num;
    };

    bool ntable[H][W] = { false, };
    for (size_t i = 0; i < H; ++i) {
        for (size_t j = 0; j < W; ++j) {
            size_t num = n_neighbor(i, j);
            if ((!table[i][j] && num == 3)
                || (table[i][j] && (num == 2 || num == 3)))
            {
                ntable[i][j] = true;
            }
        }
    }

    for (size_t i = 0; i < H; ++i) {
        for (size_t j = 0; j < W; ++j) {
            table[i][j] = ntable[i][j];
        }
    }
}

int main() {
    bool arr[20][50] = {
        { 0, 0, 1, },
        { 1, 0, 1, },
        { 0, 1, 1, },
    };

    for (size_t i = 0; i < 100; ++i) {
        for (size_t h = 0; h < 20; ++h) {
            for (size_t w = 0; w < 50; ++w) {
                std::cout << (arr[h][w] ? '*' : ' ');
            }
            std::cout << '\n';
        }
        for (size_t w = 0; w < 50; ++w) {
            std::cout << '-';
        }
        std::cout << std::endl;

        simulate(arr);
        std::this_thread::sleep_for(0.3s);
    }
}