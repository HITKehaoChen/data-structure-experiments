#include "stack.h"

bool arrayStack::isEmpty() const {
    return top == -1;
}

void arrayStack::push(BSTNode* x) {
    top += 1;
    data[top] = x;
}

BSTNode* arrayStack::pop() {
    return data[top--];
}

bool adtStack::isEmpty() const {
    return s.isEmpty();
}

void adtStack::push(BSTNode* x) {
    s.push(x);
}

BSTNode* adtStack::pop() {
    return s.pop();
}
