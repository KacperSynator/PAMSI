#ifndef GRAPH_HPP_
#define GRAPH_HPP_

#include "shortest_path_algorithms.hpp"
#include <iostream>
#include <map>

#define INF 2147483647

struct VertexResult;
using ShortestPathResult = std::map<int, VertexResult>;

class Graph
{
  public:
    virtual void dijkstra(Graph& graph, int sourceIndex, ShortestPathResult& result)=0;
    virtual bool bellmanFord(Graph& graph, int sourceIndex, ShortestPathResult& result)=0;

};

#endif /* GRAPH_HPP_ */
