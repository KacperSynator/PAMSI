#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"

#include "sorting/sorting.hpp"

#include <filesystem>
#include <fstream>

const std::filesystem::path dataDirectoryPath{DATA_DIR_PATH};

using namespace std::string_literals;

void readData(const std::filesystem::path& path, std::vector<int>& tab)
{
    std::ifstream ifs{path, std::fstream::binary};

    while(ifs)
    {
        int element;
        ifs.read(reinterpret_cast<char*>(&element), sizeof(element));

        if(ifs)
        {
            tab.push_back(element);
        }
    }
}


// TODO: Choose 3 algorithms, other tests remove



TEST_CASE("Sorting big data -- heapSort")
{
    auto dataFilePath = GENERATE(dataDirectoryPath / "sort_data_10000.bin", dataDirectoryPath / "sort_data_100000.bin",
                                 dataDirectoryPath / "sort_data_1000000.bin");
    std::vector<int> tab, refTab;

    readData(dataFilePath, tab);

    REQUIRE(tab.size() > 1);

    std::copy(tab.begin(), tab.end(), std::back_insert_iterator<std::vector<int>>(refTab));

    REQUIRE(refTab.size() > 1);

    std::sort(refTab.begin(), refTab.end());

    heapSort(tab);

    for(int i = 0; i < tab.size(); ++i)
    {
        INFO(dataFilePath.filename() << ": Checking tab[" << i << "] == refTab[" << i << "]");
        REQUIRE(tab[i] == refTab[i]);
    }
}

TEST_CASE("Sorting big data -- quicksort")
{
    auto dataFilePath = GENERATE(dataDirectoryPath / "sort_data_10000.bin", dataDirectoryPath / "sort_data_100000.bin",
                                 dataDirectoryPath / "sort_data_1000000.bin");
    std::vector<int> tab, refTab;

    readData(dataFilePath, tab);

    REQUIRE(tab.size() > 1);

    std::copy(tab.begin(), tab.end(), std::back_insert_iterator<std::vector<int>>(refTab));

    REQUIRE(refTab.size() > 1);

    std::sort(refTab.begin(), refTab.end());

    quickSort(tab);

    for(int i = 0; i < tab.size(); ++i)
    {
        INFO(dataFilePath.filename() << ": Checking tab[" << i << "] == refTab[" << i << "]");
        REQUIRE(tab[i] == refTab[i]);
    }
}

TEST_CASE("Sorting big data -- merge sort")
{
    auto dataFilePath = GENERATE(dataDirectoryPath / "sort_data_10000.bin", dataDirectoryPath / "sort_data_100000.bin",
                                 dataDirectoryPath / "sort_data_1000000.bin");
    std::vector<int> tab, refTab;

    readData(dataFilePath, tab);

    REQUIRE(tab.size() > 1);

    std::copy(tab.begin(), tab.end(), std::back_insert_iterator<std::vector<int>>(refTab));

    REQUIRE(refTab.size() > 1);

    std::sort(refTab.begin(), refTab.end());

    mergeSort(tab);

    for(int i = 0; i < tab.size(); ++i)
    {
        INFO(dataFilePath.filename() << ": Checking tab[" << i << "] == refTab[" << i << "]");
        REQUIRE(tab[i] == refTab[i]);
    }
}

TEST_CASE("Sorting big data -- bubble sort")
{
    auto dataFilePath = GENERATE(dataDirectoryPath / "sort_data_10000.bin", dataDirectoryPath / "sort_data_100000.bin",
                                 dataDirectoryPath / "sort_data_1000000.bin");
    std::vector<int> tab, refTab;

    readData(dataFilePath, tab);

    REQUIRE(tab.size() > 1);

    std::copy(tab.begin(), tab.end(), std::back_insert_iterator<std::vector<int>>(refTab));

    REQUIRE(refTab.size() > 1);

    std::sort(refTab.begin(), refTab.end());

    bubbleSort(tab);

    for(int i = 0; i < tab.size(); ++i)
    {
        INFO(dataFilePath.filename() << ": Checking tab[" << i << "] == refTab[" << i << "]");
        REQUIRE(tab[i] == refTab[i]);
    }
}