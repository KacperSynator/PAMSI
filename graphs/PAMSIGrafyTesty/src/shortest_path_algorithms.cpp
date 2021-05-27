#include "graphs/shortest_path_algorithms.hpp"

void dijkstra(Graph& graph, int sourceIndex, ShortestPathResult& result)
{
    graph.dijkstra(graph,sourceIndex,result);
}

bool bellmanFord(Graph& graph, int sourceIndex, ShortestPathResult& result)
{
    return graph.bellmanFord(graph,sourceIndex,result);
}
