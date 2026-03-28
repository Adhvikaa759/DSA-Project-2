#include "dijkstra.h"
#include <queue>
#include <unordered_map>
#include <chrono>
#include <limits>
#include <algorithm>

PathResult dijkstra(const Graph& graph, int start, int end) {
    auto startTime = std::chrono::high_resolution_clock::now();

    // dist[node] = best known cost from start to node
    std::unordered_map<int, double> dist;
    std::unordered_map<int, int> prev;
    int nodesVisited = 0;

    for (auto& [id, _] : graph.nodes)
        dist[id] = std::numeric_limits<double>::infinity();
    dist[start] = 0.0;

    // Min-heap: (cost, node)
    using PQEntry = std::pair<double, int>;
    std::priority_queue<PQEntry, std::vector<PQEntry>, std::greater<PQEntry>> pq;
    pq.push({0.0, start});

    while (!pq.empty()) {
        auto [cost, u] = pq.top();
        pq.pop();

        // Skip stale entries
        if (cost > dist[u]) continue;

        nodesVisited++;
        if (u == end) break;

        auto it = graph.adjList.find(u);
        if (it == graph.adjList.end()) continue;

        for (auto& [v, weight] : it->second) {
            double newCost = dist[u] + weight;
            if (newCost < dist[v]) {
                dist[v] = newCost;
                prev[v] = u;
                pq.push({newCost, v});
            }
        }
    }

    // Reconstruct path
    std::vector<int> path;
    if (dist[end] == std::numeric_limits<double>::infinity()) {
        // No path found
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

    return {path, dist[end], nodesVisited, ms};
}