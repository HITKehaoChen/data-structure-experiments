#include <iostream>
#include <fstream>
#include "polynomial.h"

int main() {
    std::cout << "Please input a Polynomial:" << std::endl;
    std::cout << "(The format of every term is: ax^e)" << std::endl << '\t';

    /* input the polynomials */
    Polynomial pnlFromKeyboard;
    std::cin >> pnlFromKeyboard;

    std::ifstream inputFromFile("polynomial.in", std::ios_base::in);
    Polynomial pnlFromFile;
    inputFromFile >> pnlFromFile;

    /* output the polynomials */
    std::cout << "What you have input from KEYBOARD is:" << std::endl;
    std::cout << '\t' << pnlFromKeyboard << std::endl;
    std::cout << "What you have input from FILE is:" << std::endl;
    std::cout << '\t' << pnlFromFile << std::endl;

    std::ofstream outputToFile("polynomial.out", std::ios_base::out);
    outputToFile << "What you have input from KEYBOARD is:" << std::endl;
    outputToFile << '\t' << pnlFromKeyboard << std::endl;
    outputToFile << "What you have input from FILE is:" << std::endl;
    outputToFile << '\t' << pnlFromFile << std::endl;
    std::cout << "And they are both written into a file named \"polynomial.out\"." << std::endl;
    std::cout << std::string(60, '-') << std::endl;

    /* calculate the polynomial with an input x0 */
    double x;
    std::cout << "Please input a x0:" << std::endl << '\t';
    std::cin >> x;
    std::cout << "The value of the polynomial input from KEYBOARD such that x=x0 is:" << std::endl;
    std::cout << '\t' << pnlFromKeyboard.calc(x) << std::endl;
    std::cout << std::string(60, '-') << std::endl;

    /* output the sum of inputs from KEYBOARD and FILE */
    std::cout << "The sum of inputs from FILE and KEYBOARD is:" << std::endl;
    Polynomial pnlSum = pnlFromFile + pnlFromKeyboard;
    std::cout << '\t' << pnlSum << std::endl;
    std::cout << std::string(60, '-') << std::endl;

    /* output the subtraction of inputs from KEYBOARD and FILE */
    std::cout << "The subtraction of inputs from FILE and KEYBOARD is:" << std::endl;
    Polynomial pnlSubtraction = pnlFromFile - pnlFromKeyboard;
    std::cout << '\t' << pnlSubtraction << std::endl;
    std::cout << std::string(60, '-') << std::endl;

    /* output the multiplication of inputs from KEYBOARD and FILE */
    std::cout << "The multiplication of inputs from FILE and KEYBOARD is:" << std::endl;
    Polynomial pnlMultiplication = pnlFromFile * pnlFromKeyboard;
    std::cout << '\t' << pnlMultiplication << std::endl;
    std::cout << std::string(60, '-') << std::endl;

    /* output the quotient of inputs from KEYBOARD and FILE */
    std::cout << "The quotient of inputs from FILE and KEYBOARD is:" << std::endl;
    Polynomial pnlQuotient = pnlFromFile / pnlFromKeyboard;
    std::cout << '\t' << pnlQuotient << std::endl;
    std::cout << std::string(60, '-') << std::endl;

    /* output the remainder of inputs from KEYBOARD and FILE */
    std::cout << "The remainder of inputs from FILE and KEYBOARD is:" << std::endl;
    Polynomial pnlRemainder = pnlFromFile % pnlFromKeyboard;
    std::cout << '\t' << pnlRemainder << std::endl;

    return 0;
}
