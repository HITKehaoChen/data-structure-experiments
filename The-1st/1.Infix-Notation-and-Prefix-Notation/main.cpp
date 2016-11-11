#include <iostream>
#include "stack.h"

size_t priorityTest(char);

std::string rmSpaces(std::string);

std::string infixToPostfix(std::string);

double calcPostfix(std::string);

void assignVar(std::string, double []);

int main() {
    std::string infix, postfix;
    std::getline(std::cin, infix);
    infix = rmSpaces(infix);

    std::cout << "What you have input is:" << std::endl
              << '\t' << infix << std::endl
              << "The process of conversion is:" << std::endl;

    postfix = infixToPostfix(infix);
    std::cout << "The converted postfix is:" << std::endl;
    std::cout << '\t' << postfix << std::endl;
    std::cout << std::string(30, '-') << std::endl;

    double result;
    postfix = rmSpaces(postfix);
    std::cout << "The process of calculation is:" << std::endl;
    result = calcPostfix(postfix);
    std::cout << "The value of the expression is:" << std::endl;
    std::cout << '\t' << result << std::endl;
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

std::string rmSpaces(std::string s) {
    while (s.find(' ') != std::string::npos) {
        s.erase(s.find(' '), 1);
    }
    return s;
}

std::string infixToPostfix(std::string infix) {
    /*  Input: infix notation
     *  Output: the process of conversion
     *  Return Value: the converted postfix notation
     */
    std::string postfix;
    size_t i = 0;
    char temp;
    operatorStack s;
    while (infix[i] != '\0') {
        if (isdigit(infix[i]) || isalpha(infix[i])) {
            /* if the token is an operand */
            postfix += infix[i];
            postfix += ' ';
        } else {
            /* if the token is an operator */
            if (infix[i] == '(') {               // processing with '('
                printf("\t%c pushed\n", infix[i]);
                s.push(infix[i]);
            } else if (infix[i] == ')') {       // processing with ')'
                while (!s.isEmpty() && (temp = s.pop()) != '(') {
                    printf("\t%c popped\n", temp);
                    postfix += temp;
                    postfix += ' ';
                }
            } else {                            // processing with normal operands
                while (!s.isEmpty()) {
                    temp = s.pop();
                    if (priorityTest(temp) >= priorityTest(infix[i])) {
                        printf("\t%c popped\n", temp);
                        postfix += temp;
                        postfix += ' ';
                    } else {
                        s.push(temp);
                        break;
                    }
                }
                printf("\t%c pushed\n", infix[i]);
                s.push(infix[i]);
            }
        }
        ++i;
    }
    while (!s.isEmpty()) {
        postfix += s.pop();
        postfix += ' ';
    }
    return postfix;
}

double calcPostfix(std::string postfix) {
    /*  Input: postfix notation
    *  Output: the process of calculation
    *  Return Value: the calculated result
    */
    double var[26]{};
    assignVar(postfix, var);
    for (size_t i = 0; i < 26; ++i) {
        if (var[i] != 0) {
            std::cout << "Please assign a value to the variable " << static_cast<char>(i + 'a')
                      << ':' << std::endl << '\t';
            std::cin >> var[i];
        }
    }
    double result;
    size_t i = 0;
    operandStack s;
    while (postfix[i] != '\0') {
        double temp;
        if (isdigit(postfix[i])) {
            /* if the token is an operand */
            printf("\t%.1lf pushed\n", (double) (postfix[i] - '0'));
            s.push(postfix[i] - '0');
        } else if (isalpha(postfix[i])) {
            printf("\t%.1lf pushed\n", var[postfix[i] - 'a']);
            s.push(var[postfix[i] - 'a']);
        } else {
            /* if the token is an operator */
            switch (postfix[i]) {
                case '+':
                    result = 0;
                    printf("\t%.1lf popped\n", temp = s.pop());
                    result += temp;
                    printf("\t%.1lf popped\n", temp = s.pop());
                    result += temp;
                    break;
                case '-':
                    result = 0;
                    printf("\t%.1lf popped\n", temp = s.pop());
                    result += -temp;
                    printf("\t%.1lf popped\n", temp = s.pop());
                    result += temp;
                    break;
                case '*':
                    result = 1;
                    printf("\t%.1lf popped\n", temp = s.pop());
                    result *= temp;
                    printf("\t%.1lf popped\n", temp = s.pop());
                    result *= temp;
                    break;
                case '/':
                    result = 1.0;
                    printf("\t%.1lf popped\n", temp = s.pop());
                    result *= 1.0 / temp;
                    printf("\t%.1lf popped\n", temp = s.pop());
                    result *= temp;
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

void assignVar(std::string s, double var[]) {
    size_t i = 0;
    while (s[i] != '\0') {
        if (isalpha(s[i])) {
            var[s[i] - 'a'] = 1;
        }
        ++i;
    }
}
