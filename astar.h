#pragma once
#include "graph.h"
#include "dijkstra.h" // reuse PathResult

PathResult aStar(const Graph& graph, int start, int end);