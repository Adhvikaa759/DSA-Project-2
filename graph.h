#pragma once
#include <unordered_map>
#include <vector>
#include <utility>

struct Node {
    double x, y; // 2D coordinates for heuristic
};

class Graph {
public:
    std::unordered_map<int, Node> nodes;
    std::unordered_map<int, std::vector<std::pair<int, double>>> adjList;

    void addNode(int id, double x, double y);
    void addEdge(int u, int v, double weight);
    void generateSyntheticGraph(int numNodes, int neighborsPerNode);
    int size() const { return nodes.size(); }
};
