#include <iostream>
#include <fstream>
#include <cmath>
#include <memory>
#include "graph.h"

void printGraph(const Graph& graph);

template <typename T>
std::unique_ptr<Graph> convertGraph(Graph& graphSrc);

int main() {
    std::unique_ptr<Graph> graphTest;

    // Read from file.
    std::ifstream myFile;
    myFile.open("graphInput.txt");
    std::size_t vertexNum;
    myFile >> vertexNum;
    graphTest.reset(new GListAdjacency(vertexNum));
    std::size_t edgeNum;
    myFile >> edgeNum;
    for (std::size_t i = 0; i < edgeNum; ++i) {
        std::size_t vTemp1;
        std::size_t vTemp2;
        int weight;
        myFile >> vTemp1;
        myFile >> vTemp2;
        myFile >> weight;
        (*graphTest).addEdge(vTemp1 - 1, vTemp2 - 1, weight);
    }

    std::cout << "The graph is:" << std::endl << std::endl;
    printGraph(*graphTest);
    std::cout << std::string(60, '*') << std::endl;

    // Dijkstra's Algorithm
    std::cout << "Dijkstra's algorithm from vertex 1:"
              << std::endl << std::endl;
    (*graphTest).Dijkstra(0);
    std::cout << std::string(60, '*') << std::endl;

    // Floyd's Algorithm
    std::cout << "Floyd's algorithm:" << std::endl << std::endl;
    (*graphTest).FloydWarshall();
    std::cout << std::string(60, '*') << std::endl;

    // The shortest path to the single target using Floyd's algorithm
    std::cout << "The shortest path to vertex 3 using Floyd's algorithm"
              << std::endl << std::endl;
    (*graphTest).FloydWarshall(2);
    std::cout << std::string(60, '*') << std::endl;

    // The shortest path from a to b using Floyd's algorithm
    std::cout << "The shortest path from 1 to 3 using Floyd's algorithm"
              << std::endl << std::endl;
    (*graphTest).FloydWarshall(0, 2);

    myFile.close();
    return 0;
}


/* Print */
void printGraph(const Graph& graph) {
    for (std::size_t i = 0; i < graph.getVertexNum(); ++i) {
        for (std::size_t j = 0; j < graph.getVertexNum(); ++j) {
            if (graph.isEdge(i, j)) {
                std::cout << graph.getWeight(i, j) << ' ';
            } else {
                std::cout << " 0 ";
            }
        }
        std::cout << std::endl;
    }
}

/* Three conversions */
template <typename T>
std::unique_ptr<Graph> convertGraph(Graph& graphSrc) {
    std::size_t size = graphSrc.getVertexNum();
    std::unique_ptr<Graph> graphConverted;
    graphConverted.reset(new T(size));
    for (std::size_t i = 0; i < size; ++i) {
        for (std::size_t j = 0; j < size; ++j) {
            if (graphSrc.isEdge(i, j)) {
                (*graphConverted).addEdge(i, j, graphSrc.getWeight(i, j));
            }
        }
    }
    return graphConverted;
};
