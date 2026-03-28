#include "astar.h"
#include <queue>
#include <unordered_map>
#include <chrono>
#include <limits>
#include <cmath>
#include <algorithm>

static double heuristic(const Graph& graph, int u, int goal) {
    auto itU = graph.nodes.find(u);
    auto itG = graph.nodes.find(goal);
    if (itU == graph.nodes.end() || itG == graph.nodes.end()) return 0.0;
    double dx = itU->second.x - itG->second.x;
    double dy = itU->second.y - itG->second.y;
    return std::sqrt(dx * dx + dy * dy); // Euclidean distance
}

PathResult aStar(const Graph& graph, int start, int end) {
    auto startTime = std::chrono::high_resolution_clock::now();

    std::unordered_map<int, double> gCost; // actual cost from start
    std::unordered_map<int, int> prev;
    int nodesVisited = 0;

    for (auto& [id, _] : graph.nodes)
        gCost[id] = std::numeric_limits<double>::infinity();
    gCost[start] = 0.0;

    // Min-heap: (f = g + h, node)
    using PQEntry = std::pair<double, int>;
    std::priority_queue<PQEntry, std::vector<PQEntry>, std::greater<PQEntry>> pq;
    pq.push({heuristic(graph, start, end), start});

    while (!pq.empty()) {
        auto [f, u] = pq.top();
        pq.pop();

        // Skip stale entries
        double expectedF = gCost[u] + heuristic(graph, u, end);
        if (f > expectedF + 1e-9) continue;

        nodesVisited++;
        if (u == end) break;

        auto it = graph.adjList.find(u);
        if (it == graph.adjList.end()) continue;

        for (auto& [v, weight] : it->second) {
            double newG = gCost[u] + weight;
            if (newG < gCost[v]) {
                gCost[v] = newG;
                prev[v] = u;
                double fScore = newG + heuristic(graph, v, end);
                pq.push({fScore, v});
            }
        }
    }

    // Reconstruct path
    std::vector<int> path;
    if (gCost[end] == std::numeric_limits<double>::infinity()) {
        auto endTime = std::chrono::high_resolution_clock::now();
        double ms = std::chrono::duration<double, std::milli>(endTime - startTime).count();
        return {path, -1.0, nodesVisited, ms};
    }

    for (int cur = end; cur != start; ) {
        path.push_back(cur);
        if (prev.find(cur) == prev.end()) {
            path.clear();
            break;
        }
        cur = prev[cur];
    }
    path.push_back(start);
    std::reverse(path.begin(), path.end());

    auto endTime = std::chrono::high_resolution_clock::now();
    double ms = std::chrono::duration<double, std::milli>(endTime - startTime).count();

    return {path, gCost[end], nodesVisited, ms};
}