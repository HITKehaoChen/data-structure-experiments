#include <cmath>
#include "Polynomial.h"

std::string removeWhitespaces(std::string s) {
    while (s.find(' ') != std::string::npos) {
        s.erase(s.find(' '), 1);
    }
    return s;
}

Term::Term(double x, int y) {
    coefficient = x;
    exponent = y;
}

Polynomial::Polynomial(Polynomial && x) : headPointer{x.headPointer} {}

Polynomial& Polynomial::operator=(Polynomial&& x) {
    while (headPointer != NULL) {
        Term *tempPointer = headPointer;
        headPointer = headPointer->next;
        delete (tempPointer);
    }
    headPointer = x.headPointer;
    x.headPointer = nullptr;
    return *this;
}

Polynomial::~Polynomial() {
    while (headPointer != NULL) {
        Term *tempPointer = headPointer;
        headPointer = headPointer->next;
        delete (tempPointer);
    }
}

void Polynomial::insert(Term* x) {
    if (headPointer != NULL && x != NULL) {
        x->next = headPointer;
        headPointer->prev = x;
        headPointer = x;
    } else {
        headPointer = x;
    }
}
// This function need modifying.

void Polynomial::remove(Term* x) {
    if (x->prev == NULL) {
        x->next->prev = NULL;
        this->headPointer = x->next;
    } else if (x->next == NULL) {
        x->prev->next = NULL;
    } else {
        x->prev->next = x->next;
        x->next->prev = x->prev;
    }
    delete(x);
}

void Polynomial::swap(Term* x, Term* y) {
    double temp;
    temp = x->coefficient;
    x->coefficient = y->coefficient;
    y->coefficient = temp;
    temp = x->exponent;
    x->exponent = y->exponent;
    y->exponent = temp;
}

void Polynomial::sort() {
    size_t length = this->length();
    for (size_t i = 0; i < length; ++i) {
        Term* tempPointer = this->head();
        while (tempPointer != NULL && tempPointer->next != NULL) {
            if (tempPointer->exponent < tempPointer->next->exponent) {
                this->swap(tempPointer, tempPointer->next);
            }
            tempPointer = tempPointer->next;
        }
    }
}

Term* Polynomial::head() const {
    return headPointer;
}

size_t Polynomial::length() const {
    Term* p = headPointer;
    size_t count = 0;
    while (p != NULL) {
        ++count;
        p = p->next;
    }
    return count;
}

double Polynomial::calc(double x) const {
    double sum{};
    Term* tempPointer = headPointer;
    while (tempPointer != NULL) {
        sum += tempPointer->coefficient * pow(x, tempPointer->exponent);
        tempPointer = tempPointer->next;
    }
    return sum;
}

std::istream& operator>> (std::istream& input, Polynomial& p) {
    /* Input the polynomial */
    double coefficient[10] = {};
    std::string inputPNL;
    std::getline(input, inputPNL);
    inputPNL = " " + removeWhitespaces(inputPNL); // insert a whitespace at the beginning for simplicity

    /* Process with the input */
    double inputCoefficient = 0;
    int inputExponent = 0;
    for (size_t i = 1; inputPNL[i]; ++i) {        // start at index 1 so that there is no need to
        if (isalpha(inputPNL[i])) {               // judge whether i > 0 when encounter i - 1
            if (!isdigit(inputPNL[i - 1])) {
                if (inputPNL[i - 1] == '-') {
                    inputCoefficient = -1;
                } else {
                    inputCoefficient = 1;
                }
            } else {
                inputCoefficient = double{inputPNL[i - 1] - '0'};
                if (inputPNL[i - 2] == '-') {
                    inputCoefficient = -inputCoefficient;
                }
            }
            if (inputPNL[i + 1] != '^') {
                inputExponent = 1;
            } else {
                inputExponent = int{inputPNL[i + 2] - '0'};
                i += 3;                             // skip over
            }
            coefficient[inputExponent] += inputCoefficient;
        } else if (isdigit(inputPNL[i]) && ! isalpha(inputPNL[i + 1])) {
            inputCoefficient = double{inputPNL[i] - '0'};
            if (inputPNL[i - 1] == '-') {
                inputCoefficient = -inputCoefficient;
            }
            inputExponent = 0;
            coefficient[inputExponent] += inputCoefficient;
        }
    }

    /* Stored into a Polynomial object */
    Polynomial storedPNL;
    Term* tempTerm = NULL;
    for (int i = 0; i < 10; ++i) {
        if (coefficient[i] != 0) {
            tempTerm = new Term(coefficient[i], i);
            storedPNL.insert(tempTerm);
        }
    }
    p = std::move(storedPNL);
    return input;
}

std::ostream& operator<< (std::ostream& output, const Polynomial& p) {
    Term* tempPointer = p.headPointer;
    while (tempPointer != NULL) {
        if (tempPointer != p.headPointer && tempPointer->coefficient > 0) {
            output << '+';
        }
        if (tempPointer->exponent > 0) {
            if (tempPointer->coefficient == -1) {
                output << '-';
            } else if (tempPointer->coefficient != -1
                       && tempPointer->coefficient != 1) {
                output << tempPointer->coefficient;
            }
            output << 'x';
            if (tempPointer->exponent != 1) {
                output << '^' << tempPointer->exponent;
            }
        } else {
            output << tempPointer->coefficient;
        }
        tempPointer = tempPointer->next;
    }
    return output;
}

Polynomial operator+ (const Polynomial& x, const Polynomial& y) {
    Polynomial tempPNL;
    Term* tempPointer = NULL;
    Term* tempPointerX = x.headPointer;
    Term* tempPointerY = y.headPointer;
    while (tempPointerX != NULL) {
        tempPointer = new Term;
        tempPointer->coefficient = tempPointerX->coefficient;
        tempPointer->exponent = tempPointerX->exponent;
        tempPNL.insert(tempPointer);
        tempPointerX = tempPointerX->next;
    }
    bool flag;
    while (tempPointerY != NULL) {
        tempPointer = tempPNL.headPointer;
        flag = false;
        while (tempPointer != NULL) {
            if (tempPointer->exponent == tempPointerY->exponent) {
                tempPointer->coefficient += tempPointerY->coefficient;
                flag = true;
            }
            tempPointer = tempPointer->next;
        }
        if (! flag) {
            tempPointer = new Term;
            tempPointer->coefficient = tempPointerY->coefficient;
            tempPointer->exponent = tempPointerY->exponent;
            tempPNL.insert(tempPointer);
        }
        tempPointerY = tempPointerY->next;
    }
    tempPointer = tempPNL.headPointer;
    while (tempPointer != NULL) {
        if (tempPointer->coefficient == 0) {
            tempPNL.remove(tempPointer);
        }
        tempPointer = tempPointer->next;
    }
    return tempPNL;
}

Polynomial operator- (const Polynomial& x, const Polynomial& y) {
    Term* tempPointer = y.headPointer;
    while (tempPointer != NULL) {
        tempPointer->coefficient = -tempPointer->coefficient;
        tempPointer = tempPointer->next;
    }
    return x + y;
}

Polynomial operator* (const Polynomial& pnlSrc, int x) {
    Polynomial pnlTgt;
    Term* pTermSrc = pnlSrc.headPointer;
    while (pTermSrc != NULL) {
        Term* pTermTgt = new Term;
        pTermTgt->coefficient = pTermSrc->coefficient * x;
        pTermTgt->exponent = pTermSrc->exponent;
        pnlTgt.insert(pTermTgt);
        pTermSrc = pTermSrc->next;
    }
    return pnlTgt;
}

Polynomial operator* (int x, const Polynomial& pnlSrc) {
    Polynomial pnlTgt;
    Term* pTermSrc = pnlSrc.headPointer;
    while (pTermSrc != NULL) {
        Term* pTermTgt = new Term;
        pTermTgt->coefficient = pTermSrc->coefficient * x;
        pTermTgt->exponent = pTermSrc->exponent;
        pnlTgt.insert(pTermTgt);
        pTermSrc = pTermSrc->next;
    }
    return pnlTgt;
}

Polynomial operator<< (const Polynomial& pnlSrc, int x) {
    Polynomial pnlTgt;
    Term* pTermSrc = pnlSrc.headPointer;
    while (pTermSrc != NULL) {
        Term *pTermTgt = new Term;
        pTermTgt->exponent = pTermSrc->exponent + x;
        pTermTgt->coefficient = pTermSrc->coefficient;
        pnlTgt.insert(pTermTgt);
        pTermSrc = pTermSrc->next;
    }
    return pnlTgt;
}

Polynomial operator* (const Polynomial& pnlSrc1, const Polynomial& pnlSrc2) {
    Polynomial pnlTgt;
    Term* pTermSrc1 = pnlSrc1.headPointer;
    while (pTermSrc1 != NULL) {
        Polynomial PnlTemp;
        PnlTemp = pTermSrc1->coefficient * pnlSrc2;
        PnlTemp = PnlTemp << (pTermSrc1->exponent);
        pnlTgt = PnlTemp + pnlTgt;
        pTermSrc1 = pTermSrc1->next;
    }
    return pnlTgt;
}
