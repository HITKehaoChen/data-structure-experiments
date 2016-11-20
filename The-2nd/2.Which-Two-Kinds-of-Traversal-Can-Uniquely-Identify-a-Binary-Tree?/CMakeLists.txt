cmake_minimum_required(VERSION 3.6)
project(2_Which_Two_Kinds_of_Traversal_Can_Uniquely_Identify_a_Binary_Tree_)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp queue.h BinarySearchTree.h treeConstruction.cpp)
add_executable(2_Which_Two_Kinds_of_Traversal_Can_Uniquely_Identify_a_Binary_Tree_ ${SOURCE_FILES})