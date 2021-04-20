#include "timer.hpp"

#include <thread>
#include <iostream>
#include <fstream>
#include <vector>
#include "sorting/sorting.hpp"

using namespace std::chrono_literals;

// generate file: "sort_data.txt" running "data_generator.cpp" first.
int main(int argc, char* argv[])
{

    std::ifstream ifs("sort_data.txt");
    if(!ifs.is_open()) throw "file_not_found"; // look up ^
    std::vector<std::vector<int>> data;
    std::vector<int> sizes;
    int a,size;
    while(ifs)
    {
        ifs>> size;
        sizes.push_back(size);
        std::vector<int> _data;
        for(;size>0;size--)
        {
            ifs>>a;
            _data.push_back(a);
        }
        data.push_back(_data);
        _data.clear();
    }
   /* while(!data.empty())
    {
        std::cout<< sizes[0] <<"\n";
        sizes.erase(sizes.begin());
        while(!data[0].empty())
        {
            std::cout<< data[0][0] << " ";
            data[0].erase(data[0].begin());
        }
        std::cout<< "\n";
        data.erase(data.begin());
    }*/
    std::ofstream ofs{"sort_performance.txt",std::ofstream::out};

    Timer timer;

    int i=0;
    std::cout<< "data_size mergeSort_time_s heapSort_time_s bubbleSort_time_s\n";
    ofs<< "data_size mergeSort_time_s heapSort_time_s bubbleSort_time_s\n";
    for(auto elem : data)
    {
        std::vector<int> tab_tmp = elem;
        double total_t_merge=0,total_t_heap=0,total_t_bubble=0;
        int nmax=50;
        if(elem.size()>0)
        {

            for(int j=0;j<nmax;j++)
            {
                tab_tmp = elem;
                timer.start();
                mergeSort(tab_tmp);
                timer.stop();
                total_t_merge+=timer.sInterval();

                tab_tmp = elem;
                timer.start();
                heapSort(tab_tmp);
                timer.stop();
                total_t_heap+=timer.sInterval();


                 tab_tmp=elem;
                 timer.start();
                 bubbleSort(tab_tmp);
                 timer.stop();
                 total_t_bubble+=timer.sInterval();
            }
            std::cout << sizes[i] << " " << total_t_merge/nmax << " " << total_t_heap/nmax<< " " << total_t_bubble/nmax <<"\n";
            ofs << sizes[i] << " " << total_t_merge/nmax << " " << total_t_heap/nmax<< " " << total_t_bubble/nmax <<"\n";
            i++;
        }
    }
    ofs.flush();


    return 0;
}
