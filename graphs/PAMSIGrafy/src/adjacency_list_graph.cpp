#include "graphs/adjacency_list_graph.hpp"

AdjacencyListGraph::AdjacencyListGraph(std::istream &is)
{
    int n_ver; // number of vertexes
    int n_edge; // number of edges


    is >> n_ver >> n_edge;

    list.resize(n_ver);

    int ver;
    GraphConnection connection;
    for(int i=0 ; i< n_edge;i++)
    {
        is >> ver>> connection.vertex>> connection.cost;

        list[ver].push_back(connection);
    }
}

std::unique_ptr<Graph> AdjacencyListGraph::createGraph(std::istream& is)
{
    return std::make_unique<AdjacencyListGraph>(AdjacencyListGraph(is));
}

void AdjacencyListGraph::dijkstra(Graph& graph, int sourceIndex, ShortestPathResult& result)
{
    std::vector<bool> isVerDone;
    isVerDone.resize(list.size());

    for(int i = 0; i<list.size() ;i++)
    {
        result[i].cost=INF;
        result[i].path.push_back(sourceIndex);
    }

    result[sourceIndex].cost=0;

    for(int j=0;j<list.size();j++)
    {
        int min = INF, ver;
        for (int i = 0; i < list.size(); i++)
        {
            if (!isVerDone[i] && result[i].cost <= min)
            {
                min = result[i].cost;
                ver = i;
            }
        }

        isVerDone[ver] = true;
        for (int i = 0; i < list[ver].size(); i++)
        {
            if (!isVerDone[list[ver][i].vertex] && result[list[ver][i].vertex].cost > result[ver].cost + list[ver][i].cost)
            {
                result[list[ver][i].vertex].cost = result[ver].cost + list[ver][i].cost;
                result[list[ver][i].vertex].path[0]=ver;
            }
        }
    }


    findPath(result,sourceIndex);
}

bool AdjacencyListGraph::bellmanFord(Graph& graph, int sourceIndex, ShortestPathResult& result)
{
    for(int i = 0; i<list.size() ;i++)
    {
        result[i].cost=INF;
        result[i].path.push_back(sourceIndex);
    }

    result[sourceIndex].cost=0;

    for(int k=1;k<list.size();k++)
    {
        bool changed = false;
        for(int i=0;i<list.size();i++)
        {
            for(int j=0;j<list[i].size();j++)
            {
                if( result[i].cost != INF && result[list[i][j].vertex].cost > result[i].cost + list[i][j].cost)
                {
                    changed =true;
                    result[list[i][j].vertex].cost = result[i].cost + list[i][j].cost;
                    result[list[i][j].vertex].path[0]=i;
                }
            }
        }
        if(!changed)
        {
            findPath(result,sourceIndex);
            return true;
        }
    }

    for(int i=0;i<list.size();i++)
    {
        for(int j=0;j<list[i].size();j++)
        {
            if(result[list[i][j].vertex].cost > result[i].cost + list[i][j].cost)
                return false;
        }
    }

    findPath(result,sourceIndex);
    return true;
}

void AdjacencyListGraph::findPath(ShortestPathResult &result, int sourceIndex)
{
    for(int i=0;i<result.size();i++)
    {
        int ver=result[i].path[0];
        while(ver!=sourceIndex)
        {
            ver = result[ver].path[0];
            result[i].path.push_back(ver);
        }
    }
    for(int i=0;i<result.size();i++)
    {
        int k=result[i].path.size()-1;
        for(int j=0;j<result[i].path.size()/2;j++)
        {
            std::swap(result[i].path[j],result[i].path[k--]);
        }
        result[i].path.push_back(i);
    }
    result[sourceIndex].path.pop_back();
}

