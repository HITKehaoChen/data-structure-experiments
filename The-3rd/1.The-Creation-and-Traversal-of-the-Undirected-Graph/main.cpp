#include <iostream>
#include <fstream>
#include <cmath>
#include <memory>
#include "graph.h"

void printGraph(const Graph& graph);

template <typename T>
std::unique_ptr<Graph> convertGraph(Graph& graphSrc);

int main() {

    /* The Creation of Graph with Three Expressions */
    std::size_t vertexNum;
    std::cout << "Please denote the number of vertexes:" << std::endl;
    std::cin >> vertexNum;
    std::cout << "Please select a data type for graph:" << std::endl;
    std::cout << '\t' << "1. Adjacency Matrix Presentation" << std::endl;
    std::cout << '\t' << "2. Adjacency List Presentation" << std::endl;
    std::cout << '\t' << "3. Adjacency Multi List Presentation"
              << std::endl;
    std::size_t typeNum;
    std::cin >> typeNum;
    std::unique_ptr<Graph> graphPtr;        // Use smart pointer to let user select a type with program running.
    while (true) {                  // Let user select a type.
        bool inputSuccess = true;
        switch (typeNum) {
            case 1:
                graphPtr.reset(new GMatrixAdjacency(vertexNum));
                break;
            case 2:
                graphPtr.reset(new GListAdjacency(vertexNum));
                break;
            case 3:
                graphPtr.reset(new GMultiList(vertexNum));
                break;
            default:
                inputSuccess = false;
                break;
        }
        if (inputSuccess) {
            break;
        } else {
            std::cout << "Bad input! Please check and input again!" << std::endl;
        }
    }

    std::cout << "Please denote the number of edges:" <<std::endl;
    std::size_t edgeNum;
    while (true) {
        std::cin >> edgeNum;
        std::size_t maxEdgeNum = static_cast<std::size_t>(vertexNum * (vertexNum - 1) * 0.5);
        if (edgeNum <= maxEdgeNum && edgeNum > 0) {
            break;
        } else {
            std::cout << "Check out the number of edges and input again !" << std::endl;
        }
    }

    std::cout << "Please denote " << edgeNum
              << " edges by input two number separated by space:" << std::endl
              << "(1<=x<=" << edgeNum << ')' << std::endl;

    std::size_t vTemp1 = 0;
    std::size_t vTemp2 = 0;
    for (std::size_t i = 0; i < edgeNum; ++i) {
        std::cin >> vTemp1;
        std::cin >> vTemp2;
        (*graphPtr).addEdge(vTemp1 - 1, vTemp2 - 1);
    }

    std::cout << "The graph input from screen is:" << std::endl;

    /* Output the graph in a adjacency matrix */
    printGraph(*graphPtr);

    /* Read input from file and print */      // TODO: optimize it
    std::ifstream myFile;
    myFile.open("graphInput.txt");
    std::size_t vertexNumFromFile;
    std::size_t typeNumFromFile;
    std::size_t edgeNumFromFile;
    std::unique_ptr<Graph> graphPtrFromFile;
    myFile >> vertexNumFromFile;
    myFile >> typeNumFromFile;
    myFile >> edgeNumFromFile;
    switch (typeNumFromFile) {
        case 1:
            graphPtrFromFile.reset(new GMatrixAdjacency(vertexNumFromFile));
            break;
        case 2:
            graphPtrFromFile.reset(new GListAdjacency(vertexNumFromFile));
            break;
        case 3:
            graphPtrFromFile.reset(new GMultiList(vertexNumFromFile));
            break;
        default:
            break;
    }
    for (std::size_t i = 0; i < edgeNumFromFile; ++i) {
        myFile >> vTemp1;
        myFile >> vTemp2;
        (*graphPtrFromFile).addEdge(vTemp1 - 1, vTemp2 - 1);
    }
    std::cout << "The graph input from file is:" << std::endl;
    printGraph(*graphPtrFromFile);
    myFile.close();

    ////////////////////////////////////////////////////////////////////////////////////////
    std::cout << std::string(60, '*') << std::endl;        // Separator

    /* Conversion */
    std::cout << "Now select a type you want to convert the graph type to:" << std::endl;
    std::size_t convertNum = 0;
    while (true) {
        std::cin >> convertNum;
        if (convertNum == typeNum) {
            std::cout << "Please select one of the other two !" << std::endl;
        } else if (convertNum <= 0 || convertNum >= 4) {
            std::cout << "Please check input num and input again!" << std::endl;
        } else {
            break;
        }
    }
    std::unique_ptr<Graph> graphConverted;
    if (typeNum == 1) {
        switch (convertNum) {
            case 2:
                graphConverted = convertGraph<GListAdjacency>(*graphPtr);
                break;
            case 3:
                graphConverted = convertGraph<GMultiList>(*graphPtr);
            default:
                break;
        }
    } else if (typeNum == 2) {
        switch (convertNum) {
            case 1:
                graphConverted = convertGraph<GMatrixAdjacency>(*graphPtr);
                break;
            case 3:
                graphConverted = convertGraph<GMultiList>(*graphPtr);
            default:
                break;
        }
    } else if (typeNum == 3) {
        switch (convertNum) {
            case 1:
                graphConverted = convertGraph<GMatrixAdjacency>(*graphPtr);
                break;
            case 2:
                graphConverted = convertGraph<GListAdjacency>(*graphPtr);
                break;
            default:
                break;
        }
    }
    std::cout << "Your converted graph is:" << std::endl;
    printGraph(*graphConverted);

    ////////////////////////////////////////////////////////////////////////////////////////
    std::cout << std::string(60, '*') << std::endl;        // Separator

    /* Traversal */
    std::cout << "Which kind of traversal would you like to use ?" << std::endl
              << "1. DFS with recursion." << std::endl
              << "2. DFS without recursion." << std::endl
              << "3. BFS" << std::endl;
    std::size_t traversalNum;
    while (true) {
        std::cin >> traversalNum;
        bool inputSuccess = true;
        switch (traversalNum) {
            case 1:
                std::cout << "The result of DFS with recursion is:" << std::endl;
                (*graphPtr).DFSRecursively();
                break;
            case 2:
                std::cout << "The result of DFS without recursion is:" << std::endl;
                (*graphPtr).DFSNonRecursively();
                break;
            case 3:
                std::cout << "The result of BFS is:" << std::endl;
                (*graphPtr).BFS();
                break;
            default:
                std::cout << "Please select one of the three options !" << std::endl;
                inputSuccess = false;
                break;
        }
        if (inputSuccess) {
            break;
        }
    }
    return 0;
}


/* Print */
void printGraph(const Graph& graph) {
    for (std::size_t i = 0; i < graph.getSize(); ++i) {
        for (std::size_t j = 0; j < graph.getSize(); ++j) {
            std::cout << graph.isEdge(i, j) << ' ';
        }
        std::cout << std::endl;
    }
}

/* Three conversions */
template <typename T>
std::unique_ptr<Graph> convertGraph(Graph& graphSrc) {
    std::size_t size = graphSrc.getSize();
    std::unique_ptr<Graph> graphConverted;
    graphConverted.reset(new T(size));
    for (std::size_t i = 0; i < size; ++i) {
        for (std::size_t j = 0; j < size; ++j) {
            if (graphSrc.isEdge(i, j)) {
                (*graphConverted).addEdge(i, j);
            }
        }
    }
    return graphConverted;
};
