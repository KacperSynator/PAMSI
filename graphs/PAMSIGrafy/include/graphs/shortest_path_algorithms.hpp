#ifndef SHORTEST_PATH_ALGORITHMS_HPP_
#define SHORTEST_PATH_ALGORITHMS_HPP_

#include "graphs/graph.hpp"

#include <map>
#include <utility>
#include <vector>

class Graph;

struct VertexResult
{
    int cost;
    std::vector<int> path;
};

using ShortestPathResult = std::map<int, VertexResult>;

void dijkstra(Graph& graph, int sourceIndex, ShortestPathResult& result);
bool bellmanFord(Graph& graph, int sourceIndex, ShortestPathResult& result);

#endif /* SHORTEST_PATH_ALGORITHMS_HPP_ */
