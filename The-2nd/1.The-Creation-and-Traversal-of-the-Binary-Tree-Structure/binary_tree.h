#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include <fstream>
#include <iostream>

/* Node classes */

struct Node {
    char key;
    Node* parent = nullptr;
    Node* left = nullptr;
    Node* right = nullptr;
};


/* Tree classes */

class BinaryTree {
private:
    Node* root = nullptr;
public:
    void createByString(std::string string, size_t index);

    void insert(Node*);

    void insertImproved(Node*);

    Node* Root() { return this->root; }
};

std::istream& operator>>(std::istream&, BinaryTree&);

void in_orderWalk(Node*);

#endif
