#include <iostream>
#include <random>

struct Rng {
    static std::random_device rd;
    static std::default_random_engine gen;
};
std::random_device Rng::rd;
std::default_random_engine Rng::gen(Rng::rd());

template <typename D, typename T, size_t N>
void mutate(D& dist, T (&arr)[N], double threshold = 0.05) {
    std::uniform_real_distribution<double> uniform(0.0, 1.0);
    for (size_t i = 0; i < N; ++i) {
        if (uniform(Rng::gen) < threshold) {
            arr[i] = dist(Rng::gen);
        }
    }
}

template <typename T, size_t N, size_t M>
size_t most_resemble(T (&table)[M][N], T (&target)[N]) {
    double max_prob = 0;
    size_t max_idx = 0;

    for (size_t i = 0; i < M; ++i) {
        size_t correct = 0;
        for (size_t j = 0; j < N; ++j) {
            if (table[i][j] == target[j]) {
                correct += 1;
            }
        }
        double prob = static_cast<double>(correct) / N;
        if (max_prob < prob) {
            max_prob = prob;
            max_idx = i;
        }
    }

    return max_idx;
}

template <typename T, size_t N, size_t M>
void copy_table(T (&table)[M][N], T (&target)[N]) {
    for (size_t i = 0; i < M; ++i) {
        for (size_t j = 0; j < N; ++j) {
            table[i][j] = target[j];
        }
    }
}

int main() {
    char target[] = "METHINKS IT IS LIKE A WEASEL.";
    std::string_view target_view(target);

    constexpr size_t n_succ = 10000;
    constexpr size_t width = sizeof(target);

    char table[n_succ][width] = { 0, };
    char lib[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ. ";
    std::uniform_int_distribution<size_t> uniform(0, sizeof(lib));

    auto dist = [&](auto& gen) {
        return lib[uniform(gen)];
    };

    for (size_t i = 0; i < width; ++i) {
        table[0][i] = dist(Rng::gen);
    }
    copy_table(table, table[0]);

    for (size_t gen = 0; target_view != table[0]; ++gen) {
        std::cout << "generation: " << gen << " - ";
        for (size_t i = 0; i < width; ++i) {
            std::cout << table[0][i];
        }
        std::cout << std::endl;

        for (size_t i = 0; i < n_succ; ++i) {
            mutate(dist, table[i]);
        }
        size_t idx = most_resemble(table, target);
        copy_table(table, table[idx]);
    }
}