#ifndef ADJACENCY_LIST_GRAPH_HPP_
#define ADJACENCY_LIST_GRAPH_HPP_

#include <memory>
#include <vector>

#include "graphs/graph.hpp"

class AdjacencyListGraph : public Graph
{

  public:
    struct GraphConnection{
        int vertex;
        int cost;
    };

    AdjacencyListGraph(std::istream& is);
    static std::unique_ptr<Graph> createGraph(std::istream& is);
    void dijkstra(Graph& graph, int sourceIndex, ShortestPathResult& result) override;
    bool bellmanFord(Graph& graph, int sourceIndex, ShortestPathResult& result) override;


private:
    std::vector<std::vector<GraphConnection>> list;

    void findPath(ShortestPathResult&result, int sourceIndex);

};

#endif /* ADJACENCY_LIST_GRAPH_HPP_ */
