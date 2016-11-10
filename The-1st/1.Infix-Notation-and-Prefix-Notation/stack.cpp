#include "stack.h"

bool operatorStack::isEmpty() {
    return stack.isEmpty();
}

void operatorStack::push(char x) {
    stack.push(x);
}

char operatorStack::pop() {
    return stack.pop();
}

bool operandStack::isEmpty() {
    return stack.isEmpty();
}

void operandStack::push(double x) {
    stack.push(x);
}

double operandStack::pop() {
    return stack.pop();
}
