#include <iostream>
#include "mathExpression.h"

size_t priorityTest(char);
bool infixValidator(std::string);
std::string removeWhitespaces(std::string);
std::string convertInfixToPostfix(std::string);
double calculatePostfix(std::string);

int main() {
    std::string infix, postfix;
    std::getline(std::cin, infix);
    infix = removeWhitespaces(infix);
    while (! infixValidator(infix)) {       // validate the input
        std::cout << "Please input a valid infix expression !" << std::endl;
        std::cout << "  (only digit in ones supported...)" << std::endl;
        std::getline(std::cin, infix);
    }

    std::cout << "What you have input is:" << std::endl
              << '\t' << infix << std::endl
              << "The process of conversion is:" << std::endl;

    postfix = convertInfixToPostfix(infix);
    std::cout << "The converted postfix is:" << std::endl;
    std::cout << '\t' << postfix << std::endl;
    std::cout << std::string(30, '-') << std::endl;

    double calculationResult;
    postfix = removeWhitespaces(postfix);
    std::cout << "The process of calculation is:" << std::endl;
    calculationResult = calculatePostfix(postfix);
    std::cout << "The value of the expression is:" << std::endl;
    std::cout << '\t' << calculationResult << std::endl;
    return 0;
}

size_t priorityTest(char x) {
    if (x == '*' || x == '/') {
        return 2;
    } else if (x == '+' || x == '-') {
        return 1;
    }
    return 0;
}

bool isOperator(char x) {
    switch (x) {
        case '+':
        case '-':
        case '*':
        case '/':
            return true;
        default:
            return false;
    }
}

bool isParentheses(char x) {
    switch (x) {
        case '(':
        case ')':
            return true;
        default:
            return false;
    }
}

bool infixValidator(std::string infix) {
    if (isOperator(infix[0]) || isOperator(infix[infix.length() - 1])) {
        return false;
    }
    for (size_t i = 0; i < infix.length(); ++i) {
        if (! isdigit(infix[i]) && ! isOperator(infix[i])
                && ! isParentheses(infix[i])
                || isOperator(infix[i]) && isOperator(infix[i + 1])
                || isdigit(infix[i]) && isdigit(infix[i + 1])
                || infix[i] == '(' && isOperator(infix[i + 1])
                || infix[i + 1] == ')' && isOperator(infix[i])) {
            return false;
        }
    }
    return true;
}

std::string removeWhitespaces(std::string s) {
    while (s.find(' ') != std::string::npos) {
        s.erase(s.find(' '), 1);
    }
    return s;
}

std::string convertInfixToPostfix(std::string infix) {
    /*  Input: infix notation
     *  Output: the process of conversion
     *  Return Value: the converted postfix notation
     *  */
    std::string postfix;
    size_t i = 0;
    char stackTemp;
    operatorStack s;
    while (infix[i] != '\0') {
        if (isdigit(infix[i])) {
            /* if the token is an operand */
            postfix += infix[i];
            postfix += ' ';
        } else {
            /* if the token is an operator */
            if(infix[i] == '(') {               // processing with '('
                printf("\t%c pushed\n", infix[i]);
                s.push(infix[i]);
            } else if (infix[i] == ')') {       // processing with ')'
                while (! s.isStackEmpty() && (stackTemp = s.pop()) != '(') {
                    printf("\t%c popped\n", stackTemp);
                    postfix += stackTemp;
                    postfix += ' ';
                }
            } else {                            // processing with normal operands
                while (! s.isStackEmpty()) {
                    stackTemp = s.pop();
                    if (priorityTest(stackTemp) >= priorityTest(infix[i])) {
                        printf("\t%c popped\n", stackTemp);
                        postfix += stackTemp;
                        postfix += ' ';
                    } else {
                        s.push(stackTemp);
                        break;
                    }
                }
                printf("\t%c pushed\n", infix[i]);
                s.push(infix[i]);
            }
        }
        ++i;
    }
    while (! s.isStackEmpty()) {
        postfix += s.pop();
        postfix += ' ';
    }
    return postfix;
}

double calculatePostfix(std::string postfix) {
    /*  Input: postfix notation
    *  Output: the process of calculation
    *  Return Value: the calculated result
    *  */
    double result;
    size_t i = 0;
    operandStack s;
    double stackTemp;
    while (postfix[i] != '\0') {
        if (isdigit(postfix[i])) {
            /* if the token is an operand */
            printf("\t%.1lf pushed\n", (double)(postfix[i] - '0'));
            s.push(postfix[i] - '0');
        } else {
            /* if the token is an operator */
            switch (postfix[i]) {
                case '+':
                    result = 0;
                    printf("\t%.1lf popped\n", stackTemp = s.pop());
                    result += stackTemp;
                    printf("\t%.1lf popped\n", stackTemp = s.pop());
                    result += stackTemp;
                    break;
                case '-':
                    result = 0;
                    printf("\t%.1lf popped\n", stackTemp = s.pop());
                    result += -stackTemp;
                    printf("\t%.1lf popped\n", stackTemp = s.pop());
                    result += stackTemp;
                    break;
                case '*':
                    result = 1;
                    printf("\t%.1lf popped\n", stackTemp = s.pop());
                    result *= stackTemp;
                    printf("\t%.1lf popped\n", stackTemp = s.pop());
                    result *= stackTemp;
                    break;
                case '/':
                    result = 1.0;
                    printf("\t%.1lf popped\n", stackTemp = s.pop());
                    result *= 1.0 / stackTemp;
                    printf("\t%.1lf popped\n", stackTemp = s.pop());
                    result *= stackTemp;
                    break;
                default:
                    result = 0;
                    break;
            }
            printf("\t%.1lf pushed\n", result);
            s.push(result);
        }
        ++i;
    }
    return s.pop();
}
