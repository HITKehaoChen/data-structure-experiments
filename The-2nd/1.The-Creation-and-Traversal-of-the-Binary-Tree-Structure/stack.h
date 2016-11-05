#ifndef STACK_H
#define STACK_H

#include "bst.h"

struct arrayStack {
private:
    int top = -1;
    BSTNode* data[100] = {};
public:
    bool isEmpty() const ;
    void push(BSTNode*);
    BSTNode* pop();
};

class adtStack {
private:
    arrayStack s;
public:
    bool isEmpty() const ;
    void push(BSTNode*);
    BSTNode* pop();
};

#endif
