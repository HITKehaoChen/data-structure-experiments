#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <stdexcept>
#include <vector>
#include "list.h"
#include "stack.h"
#include "queue.h"

class Graph {
private:
    virtual bool isVisited(std::size_t) const = 0;

    virtual void setVisited(std::size_t) const = 0;     // TODO: kill these two.

    virtual void restoreVisited() const = 0;

    void dfs(std::size_t vertex) const {
        std::vector<std::size_t> vertexesAdjacent(getSize());
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

    virtual void addEdge(std::size_t i, std::size_t j) = 0;

    virtual void rmEdge(std::size_t i, std::size_t j) = 0;

    virtual bool isEdge(std::size_t i, std::size_t j) const = 0;

    virtual size_t getSize() const = 0;

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
            std::vector<std::size_t> vertexesAdjacent(getSize());
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
            std::vector<std::size_t> vertexesAdjacent(getSize());
            std::vector<std::size_t>::iterator iter = vertexesAdjacent.begin();
            getAdjacent(vertexTemp, iter);
            for (iter = vertexesAdjacent.begin(); iter != vertexesAdjacent.end(); ++iter) {
                q.enQueue((*iter));
            }
        }
        restoreVisited();
    }
};

/* Adjacency Matrix Graph */

class GMatrixAdjacency : public Graph {
private:
    bool** vertex = nullptr;
    bool* visited = nullptr;
    std::size_t size = 0;

    virtual bool isVisited(std::size_t v) const override {
        return visited[v];
    }

    virtual void setVisited(std::size_t v) const override {
        visited[v] = true;
    }

    virtual void restoreVisited() const override {
        for (std::size_t i = 0; i < size; ++i) {
            visited[i] = false;
        }
    }

public:
    GMatrixAdjacency(std::size_t x) : size{x} {
        visited = new bool[size];
        vertex = new bool* [size];
        for (std::size_t i = 0; i < size; i++) {
            vertex[i] = new bool[size];
            for (std::size_t j = 0; j < size; j++) {
                vertex[i][j] = false;
            }
            visited[i] = false;
        }
    }

    GMatrixAdjacency(const GMatrixAdjacency& graphSrc) {
        vertex = new bool* [graphSrc.size];
        for (std::size_t i = 0; i < graphSrc.size; i++) {
            vertex[i] = new bool[graphSrc.size];
            for (std::size_t j = 0; j < graphSrc.size; j++) {
                vertex[i][j] = graphSrc.isEdge(i, j);
            }
        }
    }

    GMatrixAdjacency& operator=(const GMatrixAdjacency& graphSrc) {
        if (&graphSrc != this) {

            // destroy
            for (std::size_t i = 0; i < size; ++i) {
                delete[] vertex[i];
            }
            delete[] vertex;

            // copy
            vertex = new bool* [graphSrc.size];
            for (std::size_t i = 0; i < graphSrc.size; i++) {
                vertex[i] = new bool[graphSrc.size];
                for (std::size_t j = 0; j < graphSrc.size; j++) {
                    vertex[i][j] = graphSrc.isEdge(i, j);
                }
            }
        }
        return *this;
    }

    virtual ~GMatrixAdjacency() {
        for (std::size_t i = 0; i < size; ++i) {
            delete[] vertex[i];
        }
        delete[] vertex;
        delete[] visited;
    }

    virtual void addEdge(std::size_t i, std::size_t j) override {
        if (i >= 0 && i < size && j >= 0 && j < size) {
            vertex[i][j] = true;
            vertex[j][i] = true;
        } else {
            throw std::runtime_error("Segmentation Fault!");
        }
    }

    virtual void rmEdge(std::size_t i, std::size_t j) override {
        if (i >= 0 && i < size && j >= 0 && j < size) {
            if (!vertex[i][j]) {
                throw std::runtime_error("No edge to be removed!");
            } else {
                vertex[i][j] = false;
                vertex[j][i] = false;
            }
        } else {
            throw std::runtime_error("Segmentation Fault!");
        }
    }

    virtual bool isEdge(std::size_t i, std::size_t j) const override {
        if (i >= 0 && i < size && j >= 0 && j < size) {
            return vertex[i][j];
        } else {
            throw std::runtime_error("Segmentation Fault!");
        }
    }

    virtual std::size_t getSize() const override {
        return size;
    }

    virtual void getAdjacent(std::size_t vertex, std::vector<std::size_t>::iterator iterator) const override {
        for (std::size_t i = 0; i < size; ++i) {
            if (isEdge(vertex, i)) {
                *iterator = i;
                ++iterator;
            }
        }
    };

};

/* Adjacency List Graph */

class GListAdjacency : public Graph {
private:
    ListLinked<std::size_t>** vertex = nullptr;
    bool* visited = nullptr;
    std::size_t size = 0;

    virtual bool isVisited(std::size_t v) const override  {
        return visited[v];
    }

    virtual void setVisited(std::size_t v) const override {
        visited[v] = true;
    }

    virtual void restoreVisited() const override {
        for (std::size_t i = 0; i < size; ++i) {
            visited[i] = false;
        }
    }

public:
    GListAdjacency(std::size_t x) : size{x} {
        vertex = new ListLinked<std::size_t>* [size];
        visited = new bool[size];
        for (std::size_t i = 0; i < size; ++i) {
            vertex[i] = new ListLinked<std::size_t>;
            visited[i] = false;
        }
    }

    virtual ~GListAdjacency() {
        for (std::size_t i = 0; i < size; ++i) {
            delete vertex[i];
        }
        delete[] vertex;
        delete[] visited;
    }

    virtual void addEdge(std::size_t i, std::size_t j) override {
        if (i >= 0 && i < size && j >= 0 && j < size) {
            NodeLinked<std::size_t>* edgeTemp1 = new NodeLinked<std::size_t>;
            NodeLinked<std::size_t>* edgeTemp2 = new NodeLinked<std::size_t>;
            edgeTemp1->key = j;
            edgeTemp2->key = i;
            vertex[i]->insert(edgeTemp1);
            vertex[j]->insert(edgeTemp2);
        } else {
            throw std::runtime_error("Segmentation Fault!");
        }
    }

    virtual void rmEdge(std::size_t i, std::size_t j) override {
        if (i >= 0 && i < size && j >= 0 && j < size) {
            NodeLinked<std::size_t>* edgeTemp1 = vertex[i]->search(j);
            NodeLinked<std::size_t>* edgeTemp2 = vertex[j]->search(i);
            if (edgeTemp1 == nullptr || edgeTemp2 == nullptr) {
                throw std::runtime_error("No edge to be removed!");
            } else {
                vertex[i]->remove(edgeTemp1);
                vertex[j]->remove(edgeTemp2);
            }
        } else {
            throw std::runtime_error("Segmentation Fault!");
        }
    }

    virtual bool isEdge(std::size_t i, std::size_t j) const override {
        NodeLinked<std::size_t>* edgeTemp1 = vertex[i]->search(j);
        NodeLinked<std::size_t>* edgeTemp2 = vertex[j]->search(i);
        if (edgeTemp1 == nullptr || edgeTemp2 == nullptr) {
            return false;
        } else {
            return true;
        }
    }

    virtual size_t getSize() const override {
        return size;
    }

    virtual void getAdjacent(std::size_t v, std::vector<std::size_t>::iterator iterator) const override {
        NodeLinked<std::size_t>* walker = vertex[v]->getHead();
        while (walker != vertex[v]->getNil()) {
            *iterator = walker->key;
            ++iterator;
            walker = walker->next;
        }
    };

};


/* Adjacency Multi-List Graph */

struct EdgeNode {
    bool isSearched = false;
    std::size_t vertex1 = 0;
    std::size_t vertex2 = 0;
    EdgeNode* pVertex1 = nullptr;
    EdgeNode* pVertex2 = nullptr;
};

bool operator==(EdgeNode a, EdgeNode b) {
    if (a.vertex1 == b.vertex1 && a.vertex2 == b.vertex2
        || a.vertex1 == b.vertex2 && a.vertex2 == b.vertex1) {
        return true;
    } else {
        return false;
    }
}

class GMultiList : public Graph {
private:
    EdgeNode** vertex = nullptr;
    bool* visited = nullptr;
    std::size_t size = 0;


    EdgeNode* predecessor(std::size_t i, EdgeNode* edgeTemp) const {
        if (edgeTemp->vertex1 == i) {
            return edgeTemp->pVertex1;
        } else if (edgeTemp->vertex2 == i) {
            return edgeTemp->pVertex2;
        } else {
            throw std::runtime_error("Bad argument !");
        }
    }

    EdgeNode* append(std::size_t i, EdgeNode* edgeTemp) {
        EdgeNode* walker = vertex[i];
        while (walker != nullptr && predecessor(i, walker) != nullptr) {
            walker = predecessor(i, walker);
        }
        if (walker == nullptr) {    //  No edges adjacent to the vertex
            vertex[i] = edgeTemp;
        } else {
            if (walker->vertex1 == i) {
                walker->pVertex1 = edgeTemp;
            } else if (walker->vertex2 == i) {
                walker->pVertex2 = edgeTemp;
            } else {
                throw std::runtime_error("Bad argument !");
            }
        }
    }

    EdgeNode* cutAndAttach(std::size_t i, EdgeNode edgeTemp) {    // Cut out the target and attach the next to the prev
        EdgeNode* walker = vertex[i];
        if (*walker == edgeTemp) {
            vertex[i] = predecessor(i, walker);
            return walker;
        } else {
            while (walker != nullptr && ! (*predecessor(i, walker) == edgeTemp)) {
                walker = predecessor(i, walker);
            }
            if (walker != nullptr) {
                EdgeNode* next = predecessor(i, walker);
                if (walker->vertex1 == i) {
                    walker->pVertex1 = predecessor(i, next);
                } else if (walker->vertex2 == i) {
                    walker->pVertex2 = predecessor(i, next);
                } else {
                    throw std::runtime_error("Bad argument !");
                }
                return predecessor(i, walker);
            } else {
                throw std::runtime_error("No edge to be deleted !");
            }
        }
    }

    virtual bool isVisited(std::size_t v) const override {
        return visited[v];
    }

    virtual void setVisited(std::size_t v) const override {
        visited[v] = true;
    }

    virtual void restoreVisited() const override {
        for (std::size_t i = 0; i < size; ++i) {
            visited[i] = false;
        }
    }

public:
    GMultiList(std::size_t x) : size{x} {
        vertex = new EdgeNode* [size];
        visited = new bool[size];
        for (std::size_t i = 0; i < size; ++i) {
            vertex[i] = nullptr;
            visited[i] = false;
        }
    }

    virtual ~GMultiList() {
        for (std::size_t i = 0; i < size; ++i) {
            EdgeNode* walker =  vertex[i];
            while (walker != nullptr) {
                EdgeNode* temp = predecessor(i, walker);
                rmEdge(walker->vertex1, walker->vertex2);
                walker = temp;
            }
        }
        delete[] vertex;
        delete[] visited;
    }

    virtual void addEdge(std::size_t i, std::size_t j) override {
        EdgeNode* edgeTemp = new EdgeNode;
        edgeTemp->vertex1 = i;
        edgeTemp->vertex2 = j;
        append(i, edgeTemp);
        append(j, edgeTemp);
    }

    virtual void rmEdge(std::size_t i, std::size_t j) override {
        EdgeNode* edgeTemp = new EdgeNode;
        edgeTemp->vertex1 = i;
        edgeTemp->vertex2 = j;
        EdgeNode* toBeDeleted;
        toBeDeleted = cutAndAttach(i, *edgeTemp);
        toBeDeleted = cutAndAttach(j, *edgeTemp);
        delete toBeDeleted;
        delete edgeTemp;
    }

    virtual bool isEdge(std::size_t i, std::size_t j) const override {
        EdgeNode* walker = vertex[i];
        while (walker != nullptr) {
            if (walker->vertex1 == i && walker->vertex2 == j
                    || walker->vertex1 == j && walker->vertex2 == i) {
                return true;
            } else {
                walker = predecessor(i, walker);
            }
        }
        return false;
    }

    virtual size_t getSize() const override {
        return size;
    }

    virtual void getAdjacent(std::size_t v, std::vector<std::size_t>::iterator iterator) const override {
        EdgeNode* walker = vertex[v];
        while (walker != nullptr) {
            if (walker->vertex1 == v) {
                *iterator = walker->vertex2;
            } else {
                *iterator = walker->vertex1;
            }
            walker = predecessor(v, walker);
            ++iterator;
        }
    }

};

#endif
