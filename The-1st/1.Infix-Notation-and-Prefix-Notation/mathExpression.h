#ifndef CPPTEST_MATHEXPRESSION_H
#define CPPTEST_MATHEXPRESSION_H

class operatorStack {
private:
    char stack[100];
    int top = -1;
public:
    bool isStackEmpty();
    bool push(char);
    char pop();
};

class operandStack {
private:
    double stack[100];
    int top = -1;
public:
    bool isStackEmpty();
    bool push(double);
    double pop();
};

#endif //CPPTEST_MATHEXPRESSION_H
