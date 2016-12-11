#ifndef GRAPH_H
#define GRAPH_H

/*
 * All graph types present in this header fine are directed ones.
 *
 */

#include <iostream>
#include <stdexcept>
#include <vector>
#include <utility>
#include <limits>
#include "list.h"
#include "stack.h"
#include "queue.h"

class Graph {
private:
    virtual bool isVisited(std::size_t) const = 0;

    virtual void setVisited(std::size_t) const = 0;     // TODO: kill these two.

    virtual void restoreVisited() const = 0;

    void dfs(std::size_t vertex) const {
        std::vector<std::size_t> vertexesAdjacent(getVertexNum());
        std::vector<std::size_t>::iterator iter = vertexesAdjacent.begin();
        getAdjacent(vertex, iter);
        for (iter = vertexesAdjacent.begin(); iter != vertexesAdjacent.end(); ++iter) {
            if (! isVisited(*iter)) {
                setVisited(*iter);
                std::cout << *iter + 1 << ' ' << std::endl;
                dfs(*iter);
            }
        }
    }

public:
    virtual ~Graph() {}

    virtual void addEdge(std::size_t i, std::size_t j, int weight) = 0;

    virtual void rmEdge(std::size_t i, std::size_t j) = 0;

    virtual bool isEdge(std::size_t i, std::size_t j) const = 0;

    virtual int getWeight(std::size_t i, std::size_t j) const = 0;

    virtual std::size_t getVertexNum() const = 0;

    virtual void getAdjacent(std::size_t, std::vector<std::size_t>::iterator) const = 0;

    void DFSRecursively() const {
        dfs(0);
        restoreVisited();
    }

    void DFSNonRecursively() const {
        stackADT<std::size_t> s;
        s.push(0);
        while (!s.isEmpty()) {
            std::size_t vertexTemp = s.pop();
            if (isVisited(vertexTemp)) {
                continue;
            }
            setVisited(vertexTemp);
            std::cout << vertexTemp + 1 << ' ' << std::endl;
            std::vector<std::size_t> vertexesAdjacent(getVertexNum());
            std::vector<std::size_t>::iterator iter = vertexesAdjacent.begin();
            getAdjacent(vertexTemp, iter);
            for (iter = vertexesAdjacent.begin(); iter != vertexesAdjacent.end(); ++iter) {
                s.push((*iter));
            }
        }
        restoreVisited();
    }

    void BFS() const {
        Queue<std::size_t> q;
        q.enQueue(0);
        while (!q.isEmpty()) {
            std::size_t vertexTemp = q.deQueue();
            if (isVisited(vertexTemp)) {
                continue;
            }
            setVisited(vertexTemp);
            std::cout << vertexTemp + 1 << ' ' << std::endl;
            std::vector<std::size_t> vertexesAdjacent(getVertexNum());
            std::vector<std::size_t>::iterator iter = vertexesAdjacent.begin();
            getAdjacent(vertexTemp, iter);
            for (iter = vertexesAdjacent.begin(); iter != vertexesAdjacent.end(); ++iter) {
                q.enQueue((*iter));
            }
        }
        restoreVisited();
    }

    void Dijkstra(std::size_t src) const {
        // An array to record path information.
//        int* parent = new int[getVertexNum()];
        int parent[200];
        // Initialize the short path tree set and distance records;
        bool* sptSet = new bool[getVertexNum()];    // SPF: Short Path Tree
        int* dist = new int[getVertexNum()];
        for (std::size_t i = 0; i < getVertexNum(); ++i) {
            sptSet[i] = false;
            dist[i] = std::numeric_limits<int>::max();
                    // Set distance to be infinite (in fact not).
        }

        // Main Part
        dist[src] = 0;
        parent[src] = -1;
        for (std::size_t i = 0; i < getVertexNum() - 1; ++i) {
            // Pick the minimum distance vertex.
            int minimum = std::numeric_limits<int>::max();
            std::size_t minIndex = 0;
            for (std::size_t i1 = 0; i1 < getVertexNum(); ++i1) {
                if (! sptSet[i1] && dist[i1] < minimum) {
                    minimum = dist[i1];
                    minIndex = i1;
                }
            }

            // Add it into sptSet.
            sptSet[minIndex] = true;
            for (std::size_t i2 = 0; i2 < getVertexNum(); ++i2) {
                if (!sptSet[i2] && isEdge(minIndex, i2) &&
                        dist[i2] > dist[minIndex] + getWeight(minIndex, i2)) {
                    dist[i2] = dist[minIndex] + getWeight(minIndex, i2);
                    parent[i2] = static_cast<int>(minIndex);
                }
            }
        }

        // Print the distance of every node and their path information.
        for (std::size_t i = 0; i < getVertexNum(); ++i) {
            std::cout << "Index:" << i + 1 << std::endl
                      << "The Shortest Distance:" << dist[i] << std::endl;
            if (i != 0) {
                std::cout << "The shortest path is: ";
                int walker = static_cast<int>(i);
                stackADT<int> s;
                while (walker != -1) {
                    s.push(walker);
                    walker = parent[walker];
                }
                std::cout << s.pop() + 1;
                while (!s.isEmpty()) {
                    std::cout << " -> " << s.pop() + 1;
                }
                std::cout << std::endl;
            }
            std::cout << std::endl;
        }

        delete[] sptSet;
        delete[] dist;
    }
};

/* Adjacency Matrix Graph */

class GMatrixAdjacency : public Graph {
private:
    int** vertex = nullptr;
    bool* visited = nullptr;
    std::size_t vertexNum = 0;

    virtual bool isVisited(std::size_t v) const override {
        return visited[v];
    }

    virtual void setVisited(std::size_t v) const override {
        visited[v] = true;
    }

    virtual void restoreVisited() const override {
        for (std::size_t i = 0; i < vertexNum; ++i) {
            visited[i] = false;
        }
    }

public:
    GMatrixAdjacency(std::size_t x) : vertexNum{x} {
        visited = new bool[vertexNum];
        vertex = new int* [vertexNum];
        for (std::size_t i = 0; i < vertexNum; i++) {
            vertex[i] = new int[vertexNum];
            for (std::size_t j = 0; j < vertexNum; j++) {
                vertex[i][j] = 0;
            }
            visited[i] = false;
        }
    }

    GMatrixAdjacency(const GMatrixAdjacency& graphSrc) {
        vertex = new int* [graphSrc.vertexNum];
        for (std::size_t i = 0; i < graphSrc.vertexNum; i++) {
            vertex[i] = new int[graphSrc.vertexNum];
            for (std::size_t j = 0; j < graphSrc.vertexNum; j++) {
                if (graphSrc.isEdge(i, j)) {
                    vertex[i][j] = graphSrc.getWeight(i, j);
                }
            }
        }
    }

    GMatrixAdjacency& operator=(const GMatrixAdjacency& graphSrc) {
        if (&graphSrc != this) {

            // destroy
            for (std::size_t i = 0; i < vertexNum; ++i) {
                delete[] vertex[i];
            }
            delete[] vertex;

            // copy
            vertex = new int* [graphSrc.vertexNum];
            for (std::size_t i = 0; i < graphSrc.vertexNum; i++) {
                vertex[i] = new int[graphSrc.vertexNum];
                for (std::size_t j = 0; j < graphSrc.vertexNum; j++) {
                    if (graphSrc.isEdge(i, j)) {
                        vertex[i][j] = graphSrc.getWeight(i, j);
                    }
                }
            }
        }
        return *this;
    }

    virtual ~GMatrixAdjacency() {
        for (std::size_t i = 0; i < vertexNum; ++i) {
            delete[] vertex[i];
        }
        delete[] vertex;
        delete[] visited;
    }

    virtual void addEdge(std::size_t i, std::size_t j, int weight) override {
        if (i >= 0 && i < vertexNum && j >= 0 && j < vertexNum) {
            vertex[i][j] = weight;
        } else {
            throw std::runtime_error("Segmentation Fault!");
        }
    }

    virtual void rmEdge(std::size_t i, std::size_t j) override {
        if (i >= 0 && i < vertexNum && j >= 0 && j < vertexNum) {
            if (!vertex[i][j]) {
                throw std::runtime_error("No edge to be removed!");
            } else {
                vertex[i][j] = 0;
            }
        } else {
            throw std::runtime_error("Segmentation Fault!");
        }
    }

    virtual bool isEdge(std::size_t i, std::size_t j) const override {
        if (i >= 0 && i < vertexNum && j >= 0 && j < vertexNum) {
            return static_cast<bool>(vertex[i][j]);
        } else {
            throw std::runtime_error("Segmentation Fault!");
        }
    }

    virtual int getWeight(std::size_t i, std::size_t j) const override {
        if (isEdge(i, j)) {
            return vertex[i][j];
        } else {
            throw std::runtime_error("No edge from i to j !");
        }
    }

    virtual std::size_t getVertexNum() const override {
        return vertexNum;
    }

    virtual void getAdjacent(std::size_t vertex, std::vector<std::size_t>::iterator iterator) const override {
        for (std::size_t i = 0; i < vertexNum; ++i) {
            if (isEdge(vertex, i)) {
                *iterator = i;
                ++iterator;
            }
        }
    };

};

/* Adjacency List Graph */
// Every vertexes' adjacent edges are out.

class GListAdjacency : public Graph {
private:
    ListLinked<std::pair<std::size_t, int>>** vertex = nullptr;
    bool* visited = nullptr;
    std::size_t vertexNum = 0;

    virtual bool isVisited(std::size_t v) const override  {
        return visited[v];
    }

    virtual void setVisited(std::size_t v) const override {
        visited[v] = true;
    }

    virtual void restoreVisited() const override {
        for (std::size_t i = 0; i < vertexNum; ++i) {
            visited[i] = false;
        }
    }

public:
    GListAdjacency(std::size_t x) : vertexNum{x} {
        vertex = new ListLinked<std::pair<std::size_t, int>>* [vertexNum];
        visited = new bool[vertexNum];
        for (std::size_t i = 0; i < vertexNum; ++i) {
            vertex[i] = new ListLinked<std::pair<std::size_t, int>>;
            visited[i] = false;
        }
    }

    virtual ~GListAdjacency() {
        for (std::size_t i = 0; i < vertexNum; ++i) {
            delete vertex[i];
        }
        delete[] vertex;
        delete[] visited;
    }

    virtual void addEdge(std::size_t i, std::size_t j, int weight) override {
        if (i >= 0 && i < vertexNum && j >= 0 && j < vertexNum) {
            NodeLinked<std::pair<std::size_t, int>>* edgeTemp
                    = new NodeLinked<std::pair<std::size_t, int>>;
            edgeTemp->key.first = j;
            edgeTemp->key.second = weight;
            vertex[i]->insert(edgeTemp);
        } else {
            throw std::runtime_error("Segmentation Fault!");
        }
    }

    virtual void rmEdge(std::size_t i, std::size_t j) override {
        if (i >= 0 && i < vertexNum && j >= 0 && j < vertexNum) {
            std::pair<std::size_t, int> keyTemp;
            keyTemp.first = j;
            keyTemp.second = getWeight(i, j);
            NodeLinked<std::pair<std::size_t, int>>* edgeTemp
                    = vertex[i]->search(keyTemp);
            if (edgeTemp == nullptr) {
                throw std::runtime_error("No edge to be removed!");
            } else {
                vertex[i]->remove(edgeTemp);
            }
        } else {
            throw std::runtime_error("Segmentation Fault!");
        }
    }

    virtual bool isEdge(std::size_t i, std::size_t j) const override {
        std::pair<std::size_t, int> keyTemp;
        keyTemp.first = j;
        keyTemp.second = getWeight(i, j);
        NodeLinked<std::pair<std::size_t, int>>* edgeTemp
                = vertex[i]->search(keyTemp);
        if (edgeTemp == nullptr) {
            return false;
        } else {
            return true;
        }
    }

    virtual int getWeight(std::size_t i, std::size_t j) const override {
        NodeLinked<std::pair<std::size_t, int>>* edgeTemp = vertex[i]->getHead();
        while (edgeTemp != vertex[i]->getNil()) {
            if (edgeTemp->key.first == j) {
                return edgeTemp->key.second;
            }
            edgeTemp = edgeTemp->next;
        }
    }

    virtual size_t getVertexNum() const override {
        return vertexNum;
    }

    virtual void getAdjacent(std::size_t v, std::vector<std::size_t>::iterator iterator) const override {
        NodeLinked<std::pair<std::size_t, int>>* walker = vertex[v]->getHead();
        while (walker != vertex[v]->getNil()) {
            *iterator = walker->key.first;
            ++iterator;
            walker = walker->next;
        }
    };

};

#endif
