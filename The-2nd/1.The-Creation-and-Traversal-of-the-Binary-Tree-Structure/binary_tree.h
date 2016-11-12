#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include <iostream>

template<typename T>
class Node {
private:
    T key;
    Node* left = nullptr;
    Node* right = nullptr;
};

class BinaryTree {
private:
    Node* root;
public:
    void createByString(std::string string, size_t index);
};

#endif
