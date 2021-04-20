#include <algorithm>
#include <fstream>
#include <functional>
#include <iostream>
#include <iterator>
#include <random>
#include <vector>
#include <sstream>

int main(int argc, char *argv[])
{

  std::vector<int> sizes;
  unsigned int data_size_min=10000, data_size_max=100000, data_size_step=10000;
  for(unsigned int i=data_size_min; i<=data_size_max; i+=data_size_step)
      sizes.push_back(i);

  std::mt19937 rng;


  std::ofstream ofs{"sort_data.txt",std::ofstream::out};
  for(auto size: sizes)
    {
      std::vector<int> data;

      std::generate_n(std::back_insert_iterator<std::vector<int>>{data}, size,
                      std::ref(rng));

      /*std::ostringstream fileName;
      fileName << "sort_data.bin";*/


      ofs<< size << "\n";
      for(auto i: data)
        ofs<<i << " ";
      ofs<<"\n";



      std::cout << data.size() << std::endl;

    }
    ofs.flush();

  return 0;
}
