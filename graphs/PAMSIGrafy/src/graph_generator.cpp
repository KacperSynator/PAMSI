#include <algorithm>
#include <fstream>
#include <functional>
#include <iostream>
#include <iterator>
#include <random>
#include <vector>
#include <sstream>
#include <string>

int main(int argc, char *argv[])
{

    std::vector<int> sizes,densities; // number of vertexes / edge densities
    unsigned int data_size_min=200, data_size_max=1000, data_size_step=200;
    for(unsigned int i=data_size_min; i<=data_size_max; i+=data_size_step)
        sizes.push_back(i);

    for(unsigned int i=25; i<=100; i+=25)
        densities.push_back(i);

    std::random_device device;
    std::mt19937 generator(device());
    std::uniform_int_distribution<int> distribution(1, 1000);


    std::ofstream ofs_file_names{"graph_files_data.txt",std::ofstream::out};
    for(auto size: sizes)
    {

        for(auto density: densities)
        {
            std::string file_name="graphV";
            file_name+=std::to_string(size);
            file_name+='D';
            file_name+=std::to_string(density);
            file_name+=".txt";
            ofs_file_names << file_name << "\n" << size << " " <<density<<"\n";
            std::ofstream ofs{file_name,std::ofstream::out};
            int k=0;
            int tmp=5-density/25;
            ofs  <<size << " " << size * (size - 1) / tmp << "\n"; // number of vertexes / number of edges
            for (int i = 0; i < size; i++)
                for (int j = 0; j < size; j++)
                {
                    if (j != i && k % tmp == 0)
                        ofs << i << " " << j << " " << distribution(generator) << "\n";
                    k++;
                }


            ofs << size / 2 << "\n"; // source index
            std::cout << density<<" "<< size << std::endl;
            ofs.flush();
        }

    }
    ofs_file_names.flush();

    return 0;
}
