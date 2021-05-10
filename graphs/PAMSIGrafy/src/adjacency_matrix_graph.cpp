#include "graphs/adjacency_matrix_graph.hpp"

AdjacencyMatrixGraph::AdjacencyMatrixGraph(std::istream &is)
{
    int n_ver; // number of vertexes
    int n_edge; // number of edges

    is >> n_ver>> n_edge;


    matrix.resize(n_ver);

    for(int i=0;i< n_ver;i++)
        matrix[i].resize(n_ver);

    int ver1,ver2,cost;
    for(int i=0; i< n_edge;i++)
    {
        is >> ver1>> ver2>> cost;

        matrix[ver1][ver2]=cost;
    }
}

std::unique_ptr<Graph> AdjacencyMatrixGraph::createGraph(std::istream& is)
{
    return std::make_unique<AdjacencyMatrixGraph>(AdjacencyMatrixGraph(is));
}

void AdjacencyMatrixGraph::dijkstra(Graph& graph, int sourceIndex, ShortestPathResult& result)
{
    std::vector<bool> isVerDone;
    isVerDone.resize(matrix.size());

    for(int i = 0; i<matrix.size() ;i++)
    {
        result[i].cost=INF;
        result[i].path.push_back(sourceIndex);
    }

    result[sourceIndex].cost=0;

    for(int j=0;j<matrix.size();j++)
    {
        int min = INF, ver;
        for (int i = 0; i < matrix.size(); i++)
        {
            if (!isVerDone[i] && result[i].cost <= min)
            {
                min = result[i].cost;
                ver = i;
            }
        }

        isVerDone[ver] = true;
        for (int i = 0; i < matrix[ver].size(); i++)
        {
            if (matrix[ver][i]!=0 && !isVerDone[i] && result[i].cost > result[ver].cost + matrix[ver][i])
            {
                result[i].cost = result[ver].cost + matrix[ver][i];
                result[i].path[0]=ver;
            }
        }
    }

    findPath(result,sourceIndex);

}

bool AdjacencyMatrixGraph::bellmanFord(Graph& graph, int sourceIndex, ShortestPathResult& result)
{
    for(int i = 0; i<matrix.size() ;i++)
    {
        result[i].cost=INF;
        result[i].path.push_back(sourceIndex);
    }

    result[sourceIndex].cost=0;

    for(int k=1;k<matrix.size();k++)
    {
        bool changed = false;
        for(int i=0;i<matrix.size();i++)
        {
            for(int j=0;j<matrix[i].size();j++)
            {
                if( matrix[i][j] != 0&& result[i].cost != INF && result[j].cost > result[i].cost + matrix[i][j])
                {
                    changed =true;
                    result[j].cost = result[i].cost + matrix[i][j];
                    result[j].path[0]=i;
                }
            }
        }
        if(!changed)
        {
            findPath(result,sourceIndex);
            return true;
        }
    }

    for(int i=0;i<matrix.size();i++)
    {
        for(int j=0;j<matrix[i].size();j++)
        {
            if(result[j].cost > result[i].cost + matrix[i][j])
                return false;
        }
    }

    findPath(result,sourceIndex);
    return true;
}

void AdjacencyMatrixGraph::findPath(ShortestPathResult& result, int sourceIndex)
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


