#include <iostream>
#include <iomanip>
#include "graph.h"
#include "dijkstra.h"
#include "astar.h"

void printPath(const std::vector<int>& path) {
    if (path.empty()) {
        std::cout << "  No path found.\n";
        return;
    }
    for (int i = 0; i < (int)path.size(); i++) {
        std::cout << path[i];
        if (i + 1 < (int)path.size()) std::cout << " -> ";
    }
    std::cout << "\n";
}

void printResults(const std::string& label, const PathResult& result) {
    std::cout << "\n--- " << label << " ---\n";
    if (result.totalCost < 0) {
        std::cout << "  No path exists between the given nodes.\n";
    } else {
        std::cout << std::fixed << std::setprecision(4);
        std::cout << "  Total cost:     " << result.totalCost << "\n";
        std::cout << "  Nodes visited:  " << result.nodesVisited << "\n";
        std::cout << "  Runtime (ms):   " << result.runtimeMs << "\n";
        std::cout << "  Path length:    " << result.path.size() << " nodes\n";
        std::cout << "  Path: ";
        // Only print path if it's short enough to display
        if (result.path.size() <= 20) {
            printPath(result.path);
        } else {
            std::cout << result.path.front() << " -> ... -> " << result.path.back()
                      << " (" << result.path.size() << " nodes)\n";
        }
    }
}

int main() {
    srand(42); // fixed seed for reproducibility

    // --- Graph Configuration ---
    int numNodes = 100000;
    int neighborsPerNode = 5;

    std::cout << "Route Runners — Shortest Path Comparison\n";
    std::cout << "=========================================\n";
    std::cout << "Generating synthetic graph with " << numNodes
              << " nodes and ~" << neighborsPerNode << " neighbors each...\n";

    Graph graph;
    graph.generateSyntheticGraph(numNodes, neighborsPerNode);

    std::cout << "Graph generated: " << graph.size() << " nodes.\n";

    // --- User Input ---
    int source, destination;
    std::cout << "\nEnter source node (0 to " << numNodes - 1 << "): ";
    std::cin >> source;
    std::cout << "Enter destination node (0 to " << numNodes - 1 << "): ";
    std::cin >> destination;

    if (source < 0 || source >= numNodes || destination < 0 || destination >= numNodes) {
        std::cerr << "Error: Node IDs must be between 0 and " << numNodes - 1 << ".\n";
        return 1;
    }

    std::cout << "\nRunning Dijkstra's Algorithm...\n";
    PathResult dijkstraResult = dijkstra(graph, source, destination);

    std::cout << "Running A* Algorithm...\n";
    PathResult astarResult = aStar(graph, source, destination);

    // --- Print Results ---
    printResults("Dijkstra's Algorithm", dijkstraResult);
    printResults("A* Algorithm", astarResult);

    // --- Comparison Summary ---
    std::cout << "\n--- Comparison Summary ---\n";
    if (dijkstraResult.totalCost >= 0 && astarResult.totalCost >= 0) {
        std::cout << std::fixed << std::setprecision(4);
        std::cout << "  Path cost match:     "
                  << (std::abs(dijkstraResult.totalCost - astarResult.totalCost) < 1e-6
                      ? "YES (both optimal)" : "NO (check implementation)") << "\n";
        std::cout << "  Nodes visited (Dijkstra): " << dijkstraResult.nodesVisited << "\n";
        std::cout << "  Nodes visited (A*):       " << astarResult.nodesVisited << "\n";
        std::cout << "  Runtime (Dijkstra ms):    " << dijkstraResult.runtimeMs << "\n";
        std::cout << "  Runtime (A* ms):          " << astarResult.runtimeMs << "\n";
    }

    return 0;
}