#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include <iostream>

template<typename T>
class Node {
private:
    T key;
    Node* left = NULL;
    Node* right = NULL;
};

class BinaryTree {
private:
    Node* root;
public:
    void createByString(std::string string, size_t index);
};

#endif
