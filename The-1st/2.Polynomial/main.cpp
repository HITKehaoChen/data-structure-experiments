#include <iostream>
#include <fstream>
#include "Polynomial.h"

Polynomial inputPolynomial();
Polynomial BubbleSort(Polynomial);

int main() {
    std::cout << "Please input a Polynomial:" << std::endl;
    std::cout << "(The format of every term is: ax^e)" << std::endl;

    /* Input the polynomials */
    Polynomial storedPNLFromScreen, storedPNLFromFile;

    std::cin >> storedPNLFromScreen;                                    // from the screen
    std::ifstream inputFromFile("polynomial.in", std::ios_base::in);
    inputFromFile >> storedPNLFromFile;                                 // from the file

    /* Output the polynomials */
    std::cout << "What you have input (FROM SCREEN) is:" << std::endl;
    std::cout << '\t' << storedPNLFromScreen << std::endl;              // to the screen
    std::cout << "What you have input (FROM FILE) is:" << std::endl;
    std::cout << '\t' << storedPNLFromFile << std::endl;              // to the screen
    std::ofstream outputToFile("polynomial.out", std::ios_base::out);   // to the file
    outputToFile << storedPNLFromFile << std::endl;

//    /* Calculate the polynomial with an offered number */
//    double x;
//    std::cout << "Please input a x0:" << std::endl;
//    std::cin >> x;
//    std::cout << "The result (FROM SCREEN) is:" << std::endl;
//    std::cout << '\t' << storedPNLFromScreen.calc(x) << std::endl;

    /* Output the sum of input from screen & input from file */
    std::cout << "The sum of input from screen & input from file:" << std::endl;
    std::cout << BubbleSort(storedPNLFromScreen + storedPNLFromFile);

    /* Auto Destroy */
    return 0;
}

Polynomial BubbleSort(Polynomial x) {
    size_t length = x.length();
    for (size_t i = 0; i < length; ++i) {
        Term* tempPointer = x.head();
        while (tempPointer != NULL && tempPointer->next != NULL) {
            if (tempPointer->exponent < tempPointer->next->exponent) {
                x.swap(tempPointer, tempPointer->next);
            }
            tempPointer = tempPointer->next;
        }
    }
    return x;
}
