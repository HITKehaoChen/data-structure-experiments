#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <fstream>

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

class Postfix {
private:
    std::string expression;
public:

};

class Prefix {
private:
    std::string expression;
    friend std::ifstream& operator>> (std::istream&, Prefix&);
public:
    Postfix cnvToPostfix();
};

std::ifstream& operator>> (std::istream&, Prefix&);

#endif
