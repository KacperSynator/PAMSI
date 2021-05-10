#include <thread>
#include <iostream>
#include <fstream>
#include <vector>

#include "timer/timer.hpp"
#include "graphs/adjacency_list_graph.hpp"
#include "graphs/adjacency_matrix_graph.hpp"
#include "graphs/shortest_path_algorithms.hpp"

using namespace std::chrono_literals;

struct GraphData{
    int n_ver;
    int density;
};

struct  Performance{
    double bel_t;
    double dij_t;
};

// generate files running "graph_generator.cpp" first.
int main(int argc, char* argv[])
{

    std::ifstream ifs("graph_files_data.txt");
    if(!ifs.is_open()) throw "file_not_found"; // look up ^
    std::vector<GraphData> graphData_vec;
    std::vector<Performance> per_data_list;
    std::vector<Performance> per_data_matrix;

    int nmax=50;
    while(ifs)
    {

        std::string name;
        std::getline(ifs, name);
        if (name == "") std::getline(ifs, name); // after reading to _graphData line becomes empty
        if (name == "") break; // last line
        GraphData _graphData;
        ifs >> _graphData.n_ver >> _graphData.density;
        graphData_vec.push_back(_graphData);
        for(int j=0;j<2;j++)
        {
            std::ifstream ifs_data(name);
            if (!ifs_data.is_open()) throw "file_not_found";

            std::unique_ptr<Graph> graph;
            if(j==0) graph = AdjacencyListGraph::createGraph(ifs_data);
            else if(j==1) graph = AdjacencyMatrixGraph::createGraph(ifs_data);

            int sourceIndex;
            ifs_data >> sourceIndex;

            Timer timer;
            ShortestPathResult result;
            Performance per;

            per.bel_t = 0;
            per.dij_t = 0;

            for (int i = 0; i < nmax; i++) {
                timer.start();
                dijkstra(*graph, sourceIndex, result);
                timer.stop();
                per.dij_t += timer.sInterval();

                timer.start();
                bellmanFord(*graph, sourceIndex, result);
                timer.stop();
                per.bel_t += timer.sInterval();
            }

            per.dij_t = per.dij_t / nmax;
            per.bel_t = per.bel_t / nmax;

            if(j==0) per_data_list.push_back(per);
            else if(j==1) per_data_matrix.push_back(per);
        }

    }


    std::cout<< "n_vertex density  dijkstra_t_list bellman_t_list  dijkstra_t_matrix bellman_t_matrix\n";
    for(int i=0; i< graphData_vec.size()/5;i++)
        for(int j=i;j<graphData_vec.size();j+=4)
        {
            std::cout<< graphData_vec[j].n_ver << " " << graphData_vec[j].density << " " << per_data_list[j].dij_t
            << " " <<per_data_list[j].bel_t << " " << per_data_matrix[j].dij_t << " " << per_data_matrix[j].bel_t <<"\n";
        }

    return 0;
}
