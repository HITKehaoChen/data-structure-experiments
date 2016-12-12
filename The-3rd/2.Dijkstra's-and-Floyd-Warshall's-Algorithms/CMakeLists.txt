cmake_minimum_required(VERSION 3.6)
project(2_Dijkstra_s_and_Floyd_Warshall_s_Algorithms)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp graph.h list.h queue.h stack.h)
add_executable(2_Dijkstra_s_and_Floyd_Warshall_s_Algorithms ${SOURCE_FILES})