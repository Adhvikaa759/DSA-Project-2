#include "graph.h"
#include <cmath>
#include <cstdlib>
#include <algorithm>

void Graph::addNode(int id, double x, double y) {
    nodes[id] = {x, y};
}

void Graph::addEdge(int u, int v, double weight) {
    adjList[u].push_back({v, weight});
    adjList[v].push_back({u, weight}); // undirected
}

static double euclidean(const Node& a, const Node& b) {
    double dx = a.x - b.x;
    double dy = a.y - b.y;
    return std::sqrt(dx * dx + dy * dy);
}

void Graph::generateSyntheticGraph(int numNodes, int neighborsPerNode) {
    // Assign random 2D coordinates to each node
    for (int i = 0; i < numNodes; i++) {
        double x = (double)(rand() % 10000);
        double y = (double)(rand() % 10000);
        addNode(i, x, y);
    }

    // Connect each node to its closest neighbors
    for (int i = 0; i < numNodes; i++) {
        // Gather candidate neighbors
        std::vector<std::pair<double, int>> candidates;
        // Sample a window to avoid O(n^2) — check nearby IDs
        int window = std::min(numNodes - 1, neighborsPerNode * 10);
        for (int j = 1; j <= window; j++) {
            int neighbor = (i + j) % numNodes;
            double dist = euclidean(nodes[i], nodes[neighbor]);
            candidates.push_back({dist, neighbor});
        }
        std::sort(candidates.begin(), candidates.end());

        int added = 0;
        for (auto& [dist, neighbor] : candidates) {
            if (added >= neighborsPerNode) break;
            addEdge(i, neighbor, dist);
            added++;
        }
    }
}