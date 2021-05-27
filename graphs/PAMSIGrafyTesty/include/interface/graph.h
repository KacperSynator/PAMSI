#ifndef GRAPH_ALGORITHMS_GRAPH_H
#define GRAPH_ALGORITHMS_GRAPH_H
#include <interface/edge.h>
#include <interface/vertex.h>


template <typename E, typename V>
class IGraph {
public:
    virtual ~IGraph() = default;

    // metody dostepowe
    virtual std::pair<IVertex*,IVertex*> endVertices(IEdge*)=0;
    virtual IVertex* opposite(IVertex*,IEdge*) =0;
    virtual bool areAdjacent(IVertex*,IVertex*) =0;
    virtual void replaceVertex(IVertex*, V)=0;
    virtual void replaceEdge(IEdge*, E)=0;

};

#endif //GRAPH_ALGORITHMS_GRAPH_H
