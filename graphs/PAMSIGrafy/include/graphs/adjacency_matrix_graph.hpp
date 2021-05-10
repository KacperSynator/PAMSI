#ifndef ADJACENCY_MATRIX_GRAPH_HPP_
#define ADJACENCY_MATRIX_GRAPH_HPP_

#include <memory>

#include "graphs/graph.hpp"

class AdjacencyMatrixGraph : public Graph
{

  public:
    AdjacencyMatrixGraph(std::istream& is);
    static std::unique_ptr<Graph> createGraph(std::istream& is);
    void dijkstra(Graph& graph, int sourceIndex, ShortestPathResult& result) override;
    bool bellmanFord(Graph& graph, int sourceIndex, ShortestPathResult& result) override;


private:
    std::vector<std::vector<int>> matrix;

    void findPath(ShortestPathResult& result, int sourceIndex);
};

#endif /* ADJACENCY_MATRIX_GRAPH_HPP_ */
