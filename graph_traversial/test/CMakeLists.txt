cmake_minimum_required(VERSION 3.20)
project(graph_traversial)

set(CMAKE_CXX_STANDARD 23)

add_executable(test test.cpp ../graph.h ../traverser.cpp ../traverser.h ../find_path.cpp ../find_path.h ../find_path_vertex.cpp ../find_path_vertex.h ../find_path_edge.cpp ../find_path_edge.h ../check_cyclic.cpp ../check_cyclic.h ../strategy.cpp ../strategy.h ../dfs.cpp ../dfs.h ../bfs.cpp ../bfs.h ../founder.cpp ../founder.h)
target_link_libraries(test gtest gtest_main)