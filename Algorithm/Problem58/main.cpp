#include <algorithm>
#include <iostream>
#include <limits>
#include <list>
#include <tuple>
#include <unordered_map>
#include <vector>

template <typename T, typename Num = size_t>
using Graph = std::unordered_map<T, std::vector<std::tuple<T, Num>>>;

auto dijkstra(Graph<char> const& graph, char start) {
    std::list<char> queue;
    std::unordered_map<char, char> prev;
    std::unordered_map<char, size_t> dist;

    for (auto const&[vertex, g] : graph) {
        prev[vertex] = 0;
        dist[vertex] = std::numeric_limits<size_t>::max();
        queue.push_back(vertex);
    }

    dist[start] = 0;

    while (!queue.empty()) {
        char min_node = 0;
        size_t min_val = std::numeric_limits<size_t>::max();
        for (auto const& elem : queue) {
            if (min_val > dist[elem]) {
                min_node = elem;
                min_val = dist[elem];
            }
        }

        if (auto iter = std::find(queue.begin(), queue.end(), min_node); 
            iter != queue.end()) 
        {
            queue.erase(iter);
        }

        for (auto const&[node, d] : graph.at(min_node)) {
            size_t alt = min_val + d;
            if (alt < dist[node]) {
                dist[node] = alt;
                prev[node] = min_node;
            }
        }
    }
    return std::make_tuple(std::move(prev), std::move(dist));
}

int main() {
    Graph<char> graph = {
        { 'A', { { 'B', 7 }, { 'C', 9 }, { 'F', 14 } } },
        { 'B', { { 'A', 7 }, { 'C', 10 }, { 'D', 15 } } },
        { 'C', { { 'A', 9 }, { 'B', 10 }, { 'D', 11 }, { 'F', 2 } } },
        { 'D', { { 'B', 15 }, { 'C', 11 }, { 'E', 6 } } },
        { 'E', { { 'D', 6 }, { 'F', 9 } } },
        { 'F', { { 'C', 2 }, { 'E', 9 }, { 'A', 14 } } },
    };

    auto[prev, dist] = dijkstra(graph, 'A');
    for (auto const&[node, v] : graph) {
        std::cout << node << " : " << dist[node] << "\t\t";

        std::list<char> queue;
        char prev_node = node;

        while (prev_node) {
            queue.push_front(prev_node);
            prev_node = prev[prev_node];
        }

        bool flag = false;
        for (auto path : queue) {
            if (flag) {
                std::cout << " -> ";
            }
            std::cout << path << ' ';
            flag = true;
        }
        std::cout << std::endl;
    }
    return 0;
}