#pragma once
#include "graph.h"
#include <vector>

struct PathResult {
    std::vector<int> path;
    double totalCost;
    int nodesVisited;
    double runtimeMs;
};

PathResult dijkstra(const Graph& graph, int start, int end);