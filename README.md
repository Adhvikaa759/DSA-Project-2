# Route Runners — Shortest Path Comparison
**Team:** Adhvikaa Radhamugundan, Deepan Ramesh, Rithika Guntu  
**Course:** COP3530 — Data Structures and Algorithms

## Overview
Compares Dijkstra's Algorithm and A* on a synthetic weighted graph of 100,000 nodes.
Outputs path cost, nodes visited, and runtime for both algorithms.

## Requirements
- C++17 or later
- g++ compiler

## Build
g++ -O2 -std=c++17 main.cpp graph.cpp dijkstra.cpp astar.cpp -o route

## Run
./route

## Usage
1. The program generates a 100,000-node graph automatically
2. Enter a source node (0–99999)
3. Enter a destination node (0–99999)
4. Results for both algorithms are printed with path cost, nodes visited, and runtime

## File Structure
- main.cpp — entry point, user input, output formatting
- graph.h / graph.cpp — graph data structure and synthetic graph generation
- dijkstra.h / dijkstra.cpp — Dijkstra's algorithm implementation
- astar.h / astar.cpp — A* algorithm implementation
