#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <stdexcept>

class AdjacencyMatrix {
private:
    bool** vertex = nullptr;
    std::size_t size = 0;
public:
    AdjacencyMatrix(std::size_t x) : size{x} {
        vertex = new bool*[size];
        for (std::size_t i = 0; i < size; i++) {
            vertex[i] = new bool[size];
            for (std::size_t j = 0; j < size; j++) {
                vertex[i][j] = false;
            }
        }
    }

    ~AdjacencyMatrix() {
        for (std::size_t i = 0; i < size; ++i) {
            delete[] vertex[i];
        }
        delete[] vertex;
    }

    void addEdge(std::size_t i, std::size_t j) {
        if (i >= 0 && i < size && j >= 0 && j < size) {
            vertex[i][j] = true;
            vertex[j][i] = true;
        } else {
            throw std::runtime_error("Segmentation Fault!");
        }
    }

    void rmEdge(std::size_t i, std::size_t j) {
        if (i >= 0 && i < size && j >= 0 && j < size) {
            vertex[i][j] = false;
            vertex[j][i] = false;
        } else {
            throw std::runtime_error("Segmentation Fault!");
        }
    }

    bool isEdge(std::size_t i, std::size_t j) const {
        if (i >= 0 && i < size && j >= 0 && j < size) {
            return vertex[i][j];
        } else {
            throw std::runtime_error("Segmentation Fault!");
        }
    }
};

class AdjacencyList {
private:

public:
};

#endif
