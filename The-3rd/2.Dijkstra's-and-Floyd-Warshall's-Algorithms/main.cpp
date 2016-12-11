#include <iostream>
#include <cmath>
#include <memory>
#include "graph.h"

void printGraph(const Graph& graph);

template <typename T>
std::unique_ptr<Graph> convertGraph(Graph& graphSrc);

int main() {
    std::unique_ptr<Graph> graphTest;
    std::size_t vertexNum = 5;
    graphTest.reset(new GListAdjacency(vertexNum));
    (*graphTest).addEdge(0, 1, 10);
    (*graphTest).addEdge(0, 3, 30);
    (*graphTest).addEdge(0, 4, 100);
    (*graphTest).addEdge(1, 2, 50);
    (*graphTest).addEdge(2, 3, 20);
    (*graphTest).addEdge(2, 4, 10);
    (*graphTest).addEdge(3, 2, 20);
    (*graphTest).addEdge(3, 4, 60);
    printGraph(*graphTest);
    std::cout << std::string(60, '*') << std::endl;
    (*graphTest).FloydWarshall();

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
