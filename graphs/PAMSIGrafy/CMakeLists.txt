cmake_minimum_required(VERSION 3.10)
project(graph_algorithms)

set (CMAKE_CXX_STANDARD 17)

link_libraries(stdc++fs)

add_library(graph_algorithms_lib src/adjacency_list_graph.cpp src/adjacency_matrix_graph.cpp src/graph_generator.cpp src/timer.cpp)
target_include_directories(graph_algorithms_lib PUBLIC include/)

add_executable(test_graphs
        src/test_graphs.cpp src/shortest_path_algorithms.cpp)
target_link_libraries(test_graphs graph_algorithms_lib)
target_compile_definitions(test_graphs PUBLIC DATA_DIR_PATH="${CMAKE_CURRENT_SOURCE_DIR}/data/")

add_executable(efficiency_tests  src/main.cpp src/timer.cpp src/shortest_path_algorithms.cpp)
target_link_libraries(efficiency_tests graph_algorithms_lib)

add_executable(data_generator src/graph_generator.cpp)
target_link_libraries(efficiency_tests graph_algorithms_lib)