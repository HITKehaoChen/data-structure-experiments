cmake_minimum_required(VERSION 3.5)
project(CPPTest)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp binary_tree.h binary_tree.cpp queue.h stack.cpp stack.h)
add_executable(CPPTest ${SOURCE_FILES})