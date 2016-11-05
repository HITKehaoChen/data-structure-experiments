#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <fstream>
#include "stack.h"

struct BSTNode {
    BSTNode* parent = NULL;
    BSTNode* right = NULL;
    BSTNode* left = NULL;
    int key;
};

struct BST {
private:
    BSTNode* head = NULL;
public:
    void insert(BSTNode*);
    /* three modes of traversal: 0 for pre-order, 1 for in-order & 2 for post-order */
    std::string traversal(size_t mode, bool isRecursive);
};

#endif

void inOrderTreeWalk(BSTNode*, std::stringstream&);

void preOrderTreeWalk(BSTNode*, std::stringstream&);

void postOrderTreeWalk(BSTNode*, std::stringstream&);
