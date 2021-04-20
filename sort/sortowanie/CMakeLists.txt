cmake_minimum_required(VERSION 3.10)
project(sorting_algorithms)

set (CMAKE_CXX_STANDARD 17)

add_library(sorting src/sorting.cpp)
target_include_directories(sorting PUBLIC include)

add_executable(test_sorting
  src/test_sorting.cpp
  )

target_link_libraries(test_sorting sorting)
target_compile_definitions(test_sorting PUBLIC DATA_DIR_PATH="${CMAKE_CURRENT_SOURCE_DIR}/data/")

add_executable(data_generator src/data_generator.cpp)

add_executable(sorting_performance src/sorting_performance.cpp src/timer.cpp)
target_link_libraries(sorting_performance PRIVATE sorting)
