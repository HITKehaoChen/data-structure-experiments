#include <cmath>
#include "polynomial.h"

std::string rmSpaces(std::string s) {
    while (s.find(' ') != std::string::npos) {
        s.erase(s.find(' '), 1);
    }
    return s;
}

Term::Term(double x, int y) {
    coefficient = x;
    exponent = y;
}

Polynomial::Polynomial(const Polynomial& x) {
    Term* pTermSrc;
    pTermSrc = x.head;
    while (pTermSrc != NULL) {
        Term* pTermTgt = new Term;
        pTermTgt->coefficient = pTermSrc->coefficient;
        pTermTgt->exponent = pTermSrc->exponent;
        insert(pTermTgt);
        pTermSrc = pTermSrc->next;
    }
    sort();
}

Polynomial& Polynomial::operator=(const Polynomial& x) {
    while (head != NULL) {
        Term *temp = head;
        head = head->next;
        delete(temp);
    }
    Term* pTermSrc;
    pTermSrc = x.head;
    while (pTermSrc != NULL) {
        Term* pTermTgt = new Term;
        pTermTgt->coefficient = pTermSrc->coefficient;
        pTermTgt->exponent = pTermSrc->exponent;
        insert(pTermTgt);
        pTermSrc = pTermSrc->next;
    }
    sort();
    return *this;
}

Polynomial::Polynomial(Polynomial && x) : head{x.head} {
    x.head = nullptr;
}

Polynomial& Polynomial::operator=(Polynomial&& x) {
    while (head != NULL) {
        Term *temp = head;
        head = head->next;
        delete(temp);
    }
    head = x.head;
    x.head = nullptr;
    return *this;
}

Polynomial::~Polynomial() {
    while (head != NULL) {
        Term *temp = head;
        head = head->next;
        delete(temp);
    }
}

void Polynomial::insert(Term* x) {
    if (head != NULL && x != NULL) {
        x->next = head;
        head->prev = x;
        head = x;
    } else {
        head = x;
    }
}

void Polynomial::remove(Term* x) {
    if (x->prev == NULL) {
        if (x->next != NULL) {
            x->next->prev = NULL;
        }
        head = x->next;
    } else if (x->next == NULL) {
        x->prev->next = NULL;
    } else {
        x->prev->next = x->next;
        x->next->prev = x->prev;
    }
    delete(x);
}

void Polynomial::swap(Term* x, Term* y) {
    double tempC;
    int tempExp;
    tempC = x->coefficient;
    x->coefficient = y->coefficient;
    y->coefficient = tempC;
    tempExp = x->exponent;
    x->exponent = y->exponent;
    y->exponent = tempExp;
}

void Polynomial::sort() {
    for (size_t i = 0; i < length(); ++i) {
        Term* pTerm = head;
        while (pTerm != NULL && pTerm->next != NULL) {
            if (pTerm->exponent < pTerm->next->exponent) {
                swap(pTerm, pTerm->next);
            }
            pTerm = pTerm->next;
        }
    }
}

size_t Polynomial::length() const {
    Term* pTerm = head;
    size_t count = 0;
    while (pTerm != NULL) {
        ++count;
        pTerm = pTerm->next;
    }
    return count;
}

double Polynomial::calc(double x) const {
    double sum{};
    Term* pTerm = head;
    while (pTerm != NULL) {
        sum += pTerm->coefficient * pow(x, pTerm->exponent);
        pTerm = pTerm->next;
    }
    return sum;
}

std::istream& operator>> (std::istream& input, Polynomial& pnlSrc) {
    /* Input the polynomial */
    double coefficient[10] = {};
    std::string pnlInput;
    std::getline(input, pnlInput);
    pnlInput = " " + rmSpaces(pnlInput); // insert a whitespace at the beginning for simplicity

    /* Process with the input */
    double cInput = 0;
    int expInput = 0;
    for (size_t i = 1; pnlInput[i]; ++i) {        // start at index 1 so that there is no need to
        if (isalpha(pnlInput[i])) {               // judge whether i > 0 when encounter i - 1
            if (!isdigit(pnlInput[i - 1])) {
                if (pnlInput[i - 1] == '-') {
                    cInput = -1;
                } else {
                    cInput = 1;
                }
            } else {
                cInput = double{pnlInput[i - 1] - '0'};
                if (pnlInput[i - 2] == '-') {
                    cInput = -cInput;
                }
            }
            if (pnlInput[i + 1] != '^') {
                expInput = 1;
            } else {
                expInput = int{pnlInput[i + 2] - '0'};
                i += 3;                             // skip over
            }
            coefficient[expInput] += cInput;
        } else if (isdigit(pnlInput[i]) && ! isalpha(pnlInput[i + 1])) {
            cInput = double{pnlInput[i] - '0'};
            if (pnlInput[i - 1] == '-') {
                cInput = -cInput;
            }
            expInput = 0;
            coefficient[expInput] += cInput;
        }
    }

    /* Stored into a Polynomial object */
    Polynomial pngTgt;
    for (int i = 0; i < 10; ++i) {
        if (coefficient[i] != 0) {
            Term* pTerm = new Term(coefficient[i], i);
            pngTgt.insert(pTerm);
        }
    }
    pnlSrc = std::move(pngTgt);       // use move() to change to r-value
    return input;
}

std::ostream& operator<< (std::ostream& output, const Polynomial& p) {
    Term* pTerm = p.head;
    if (pTerm == NULL) {
        output << '0';
        return output;
    }
    while (pTerm != NULL) {
        if (pTerm != p.head && pTerm->coefficient > 0) {
            output << '+';
        }
        if (pTerm->exponent > 0) {
            if (pTerm->coefficient == -1) {
                output << '-';
            } else if (pTerm->coefficient != -1
                       && pTerm->coefficient != 1) {
                output << pTerm->coefficient;
            }
            output << 'x';
            if (pTerm->exponent != 1) {
                output << '^' << pTerm->exponent;
            }
        } else {
            output << pTerm->coefficient;
        }
        pTerm = pTerm->next;
    }
    return output;
}

Polynomial operator+ (const Polynomial& x, const Polynomial& y) {
    Polynomial pnlTgt;
    Term* pTermX = x.head;
    Term* pTermY = y.head;

    /* copy the whole X */
    while (pTermX != NULL) {
        Term* pTermTgt = new Term;
        pTermTgt->coefficient = pTermX->coefficient;
        pTermTgt->exponent = pTermX->exponent;
        pnlTgt.insert(pTermTgt);
        pTermX = pTermX->next;
    }

    /* add terms from Y */
    while (pTermY != NULL) {     // add coefficient directly when the term already exists
        Term* pTermTgt;
        pTermTgt = pnlTgt.head;
        bool flag = false;
        while (pTermTgt != NULL) {
            if (pTermTgt->exponent == pTermY->exponent) {
                pTermTgt->coefficient += pTermY->coefficient;
                flag = true;
            }
            pTermTgt = pTermTgt->next;
        }
        if (! flag) {
            pTermTgt = new Term;
            pTermTgt->coefficient = pTermY->coefficient;
            pTermTgt->exponent = pTermY->exponent;
            pnlTgt.insert(pTermTgt);
        }
        pTermY = pTermY->next;
    }

    /* Search for zero term */
    Term* pTermTgt;
    pTermTgt = pnlTgt.head;
    while (pTermTgt != NULL) {
        if (pTermTgt->coefficient == 0) {
            pnlTgt.remove(pTermTgt);
        }
        pTermTgt = pTermTgt->next;
    }

    pnlTgt.sort();
    return pnlTgt;
}

Polynomial operator+ (const Polynomial& pnlSrc, int x) {
    Polynomial pnlTgt;
    Term* pTermSrc = pnlSrc.head;
    while(pTermSrc != NULL) {
        if (pTermSrc->exponent == 0) {
            pTermSrc->coefficient += x;
        }
        Term* pTermTgt = new Term;
        pTermTgt->coefficient = pTermSrc->coefficient;
        pTermTgt->exponent = pTermSrc->exponent;
        pnlTgt.insert(pTermTgt);
        pTermSrc = pTermSrc->next;
    }
    pnlTgt.sort();
    return pnlTgt;
}

Polynomial operator+ (int x, const Polynomial& pnlSrc) {
    Polynomial pnlTgt;
    Term* pTermSrc = pnlSrc.head;
    while(pTermSrc != NULL) {
        if (pTermSrc->exponent == 0) {
            pTermSrc->coefficient += x;
        }
        Term* pTermTgt = new Term;
        pTermTgt->coefficient = pTermSrc->coefficient;
        pTermTgt->exponent = pTermSrc->exponent;
        pnlTgt.insert(pTermTgt);
        pTermSrc = pTermSrc->next;
    }
    pnlTgt.sort();
    return pnlTgt;
}

Polynomial operator- (const Polynomial& x, const Polynomial& y) {
    Polynomial pnlTemp;
    Term* pTermY = y.head;
    while (pTermY != NULL) {
        Term* pTermTemp = new Term;
        pTermTemp->coefficient = -pTermY->coefficient;
        pTermTemp->exponent = pTermY->exponent;
        pnlTemp.insert(pTermTemp);
        pTermY = pTermY->next;
    }
    pnlTemp = x + pnlTemp;
    pnlTemp.sort();
    return pnlTemp;
}

Polynomial operator* (const Polynomial& pnlSrc, int x) {
    Polynomial pnlTgt;
    Term* pTermSrc = pnlSrc.head;
    while (pTermSrc != NULL) {
        Term* pTermTgt = new Term;
        pTermTgt->coefficient = pTermSrc->coefficient * x;
        pTermTgt->exponent = pTermSrc->exponent;
        pnlTgt.insert(pTermTgt);
        pTermSrc = pTermSrc->next;
    }
    pnlTgt.sort();
    return pnlTgt;
}

Polynomial operator* (int x, const Polynomial& pnlSrc) {
    Polynomial pnlTgt;
    Term* pTermSrc = pnlSrc.head;
    while (pTermSrc != NULL) {
        Term* pTermTgt = new Term;
        pTermTgt->coefficient = pTermSrc->coefficient * x;
        pTermTgt->exponent = pTermSrc->exponent;
        pnlTgt.insert(pTermTgt);
        pTermSrc = pTermSrc->next;
    }
    pnlTgt.sort();
    return pnlTgt;
}

Polynomial operator<< (const Polynomial& pnlSrc, int x) {
    Polynomial pnlTgt;
    Term* pTermSrc = pnlSrc.head;
    while (pTermSrc != NULL) {
        Term *pTermTgt = new Term;
        pTermTgt->exponent = pTermSrc->exponent + x;
        pTermTgt->coefficient = pTermSrc->coefficient;
        pnlTgt.insert(pTermTgt);
        pTermSrc = pTermSrc->next;
    }
    pnlTgt.sort();
    return pnlTgt;
}

Polynomial operator* (const Polynomial& x, const Polynomial& y) {
    Polynomial pnlTgt;
    Term* pTermX = x.head;
    while (pTermX != NULL) {
        Polynomial pnlTemp;
        pnlTemp = pTermX->coefficient * y;
        pnlTemp = pnlTemp << (pTermX->exponent);
        pnlTgt = pnlTemp + pnlTgt;
        pTermX = pTermX->next;
    }
    pnlTgt.sort();
    return pnlTgt;
}

Polynomial operator/ (const Polynomial& x, const Polynomial& y) {
    Polynomial pnlDividend = x;
    Polynomial pnlDivisor = y;
    Polynomial pnlResult;
    Term* pTermDividend = pnlDividend.head;
    if (pnlDividend.head->exponent < pnlDivisor.head->exponent) {
        return pnlDividend;
    }
    while (pTermDividend != NULL && pTermDividend->exponent >= pnlDivisor.head->exponent) {
        Term* termResult = new Term;
        termResult->coefficient = pTermDividend->coefficient / pnlDivisor.head->coefficient;
        termResult->exponent = pTermDividend->exponent - pnlDivisor.head->exponent;
        pnlResult.insert(termResult);
        pnlDividend = pnlDividend - ((pnlDivisor * termResult->coefficient)
                << termResult->exponent);
        pTermDividend = pnlDividend.head;
    }
    pnlResult.sort();
    return pnlResult;
}

Polynomial operator% (const Polynomial& x, const Polynomial& y) {
    Polynomial pnlDividend = x;
    Polynomial pnlDivisor = y;
    Polynomial pnlResult;
    Term* pTermDividend = pnlDividend.head;
    if (pnlDividend.head->exponent < pnlDivisor.head->exponent) {
        return pnlDividend;
    }
    while (pTermDividend != NULL && pTermDividend->exponent >= pnlDivisor.head->exponent) {
        Term* termResult = new Term;
        termResult->coefficient = pTermDividend->coefficient / pnlDivisor.head->coefficient;
        termResult->exponent = pTermDividend->exponent - pnlDivisor.head->exponent;
        pnlResult.insert(termResult);
        pnlDividend = pnlDividend - ((pnlDivisor * termResult->coefficient)
                << termResult->exponent);
        pTermDividend = pnlDividend.head;
    }
    pnlDividend.sort();
    return pnlDividend;
}
