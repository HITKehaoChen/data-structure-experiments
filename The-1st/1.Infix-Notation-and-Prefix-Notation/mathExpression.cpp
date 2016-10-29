#include <iostream>
#include "mathExpression.h"


bool operatorStack::isStackEmpty() {
    return top == -1;
}

bool operatorStack::push(char x) {
    top += 1;
    if (top >= 100) {
        std::cout << "Stack overflow !" << std::endl;
        return false;
    } else {
        stack[top] = x;
        return true;
    }
}

char operatorStack::pop() {
    if (top == -1) {
        std::cout << "Stack underflow !" << std::endl;
        return '\0';
    } else {
        top -= 1;
        return stack[top + 1];
    }
}

bool operandStack::isStackEmpty() {
    return top == -1;
}

bool operandStack::push(double x) {
    top += 1;
    if (top >= 100) {
        std::cout << "Stack overflow !" << std::endl;
        return false;
    } else {
        stack[top] = x;
        return true;
    }
}

double operandStack::pop() {
    if (top == -1) {
        std::cout << "Stack underflow !" << std::endl;
        return 10;      // return 10 because the element
    } else {            // should never be greater than 10
        top -= 1;
        return stack[top + 1];
    }
}
