#include <cmath>
#include "polynomial.h"

void rmSpaces(std::string& s) {
    while (s.find(' ') != std::string::npos) {
        s.erase(s.find(' '), 1);
    }
}

Term::Term(double x, int y) {
    coefficient = x;
    exponent = y;
}

Polynomial::Polynomial(const Polynomial& x) {
    Term* pSrc;
    pSrc = x.head;
    while (pSrc != nullptr) {
        Term* pDest = new Term;
        pDest->coefficient = pSrc->coefficient;
        pDest->exponent = pSrc->exponent;
        insert(pDest);
        pSrc = pSrc->next;
    }
    sort();
}

Polynomial& Polynomial::operator=(const Polynomial& x) {
    while (head != nullptr) {
        Term *p = head;
        head = head->next;
        delete(p);
    }
    Term* pSrc;
    pSrc = x.head;
    while (pSrc != nullptr) {
        Term* pDest = new Term;
        pDest->coefficient = pSrc->coefficient;
        pDest->exponent = pSrc->exponent;
        insert(pDest);
        pSrc = pSrc->next;
    }
    sort();
    return *this;
}

Polynomial::Polynomial(Polynomial && x) : head{x.head} {
    x.head = nullptr;
}

Polynomial& Polynomial::operator=(Polynomial&& x) {
    while (head != nullptr) {
        Term *p = head;
        head = head->next;
        delete(p);
    }
    head = x.head;
    x.head = nullptr;
    return *this;
}

Polynomial::~Polynomial() {
    while (head != nullptr) {
        Term *p = head;
        head = head->next;
        delete(p);
    }
}

void Polynomial::insert(Term* x) {
    if (head != nullptr && x != nullptr) {
        x->next = head;
        head->prev = x;
        head = x;
    } else {
        head = x;
    }
}

Term* Polynomial::remove(Term* x) {
    Term* p = x->next;
    if (x->prev == nullptr) {
        if (x->next != nullptr) {
            x->next->prev = nullptr;
        }
        head = x->next;
    } else if (x->next == nullptr) {
        x->prev->next = nullptr;
    } else {
        x->prev->next = x->next;
        x->next->prev = x->prev;
    }
    delete(x);
    return p;
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
        Term* p = head;
        while (p != nullptr && p->next != nullptr) {
            if (p->exponent < p->next->exponent) {
                swap(p, p->next);
            }
            p = p->next;
        }
    }
}

size_t Polynomial::length() const {
    Term* p = head;
    size_t count = 0;
    while (p != nullptr) {
        ++count;
        p = p->next;
    }
    return count;
}

double Polynomial::calc(double x) const {
    double sum{};
    Term* p = head;
    while (p != nullptr) {
        sum += p->coefficient * pow(x, p->exponent);
        p = p->next;
    }
    return sum;
}

std::istream& operator>> (std::istream& input, Polynomial& dest) {
    /* Input the polynomial */
    double coefficient[10] = {};
    std::string inputString;
    std::getline(input, inputString);
    rmSpaces(inputString);
    inputString = ' ' + inputString;// insert a whitespace at the beginning for simplicity

    /* Process with the input */
    double cInput = 0;
    int expInput = 0;
    for (size_t i = 1; inputString[i]; ++i) {        // start at index 1 so that there is no need to
        if (isalpha(inputString[i])) {               // judge whether i > 0 when encounter i - 1
            if (!isdigit(inputString[i - 1])) {
                if (inputString[i - 1] == '-') {
                    cInput = -1;
                } else {
                    cInput = 1;
                }
            } else {
                cInput = double{inputString[i - 1] - '0'};
                if (inputString[i - 2] == '-') {
                    cInput = -cInput;
                }
            }
            if (inputString[i + 1] != '^') {
                expInput = 1;
            } else {
                expInput = int{inputString[i + 2] - '0'};
                i += 3;                             // skip over
            }
            coefficient[expInput] += cInput;
        } else if (isdigit(inputString[i]) && ! isalpha(inputString[i + 1])) {
            cInput = double{inputString[i] - '0'};
            if (inputString[i - 1] == '-') {
                cInput = -cInput;
            }
            expInput = 0;
            coefficient[expInput] += cInput;
        }
    }

    /* Stored into a Polynomial object */
    Polynomial temp;
    for (int i = 0; i < 10; ++i) {
        if (coefficient[i] != 0) {
            Term* p = new Term(coefficient[i], i);
            temp.insert(p);
        }
    }
    dest = std::move(temp);       // use move() to change to r-value
    return input;
}

std::ostream& operator<< (std::ostream& output, const Polynomial& src) {
    Term* p = src.head;
    if (p == nullptr) {
        output << '0';
        return output;
    }
    while (p != nullptr) {
        if (p != src.head && p->coefficient > 0) {
            output << '+';
        }
        if (p->exponent > 0) {
            if (p->coefficient == -1) {
                output << '-';
            } else if (p->coefficient != -1
                       && p->coefficient != 1) {
                output << p->coefficient;
            }
            output << 'x';
            if (p->exponent != 1) {
                output << '^' << p->exponent;
            }
        } else {
            output << p->coefficient;
        }
        p = p->next;
    }
    return output;
}

Polynomial operator+ (const Polynomial& x, const Polynomial& y) {
    Polynomial dest;
    Term* pX = x.head;
    Term* pY = y.head;

    /* copy the whole X */
    while (pX != nullptr) {
        Term* pDest = new Term;
        pDest->coefficient = pX->coefficient;
        pDest->exponent = pX->exponent;
        dest.insert(pDest);
        pX = pX->next;
    }

    /* add terms from Y */
    while (pY != nullptr) {     // add coefficient directly when the term already exists
        Term* pDest;
        pDest = dest.head;
        bool flag = false;
        while (pDest != nullptr) {
            if (pDest->exponent == pY->exponent) {
                pDest->coefficient += pY->coefficient;
                flag = true;
            }
            pDest = pDest->next;
        }
        if (! flag) {
            pDest = new Term;
            pDest->coefficient = pY->coefficient;
            pDest->exponent = pY->exponent;
            dest.insert(pDest);
        }
        pY = pY->next;
    }

    /* Search for zero term */
    Term* pDest;
    pDest = dest.head;
    while (pDest != nullptr) {
        if (pDest->coefficient == 0) {
            pDest = dest.remove(pDest);
            continue;
        }
        pDest = pDest->next;
    }
    dest.sort();
    return dest;
}

Polynomial operator+ (const Polynomial& src, int x) {
    Polynomial dest;
    Term* pSrc = src.head;
    while(pSrc != nullptr) {
        if (pSrc->exponent == 0) {
            pSrc->coefficient += x;
            if (pSrc->coefficient == 0) {
                continue;
            }
        }
        Term* pDest = new Term;
        pDest->coefficient = pSrc->coefficient;
        pDest->exponent = pSrc->exponent;
        dest.insert(pDest);
        pSrc = pSrc->next;
    }
    dest.sort();
    return dest;
}

Polynomial operator+ (int x, const Polynomial& src) {
    Polynomial dest;
    Term* pSrc = src.head;
    while(pSrc != nullptr) {
        if (pSrc->exponent == 0) {
            pSrc->coefficient += x;
            if (pSrc->coefficient == 0) {
                continue;
            }
        }
        Term* pDest = new Term;
        pDest->coefficient = pSrc->coefficient;
        pDest->exponent = pSrc->exponent;
        dest.insert(pDest);
        pSrc = pSrc->next;
    }
    dest.sort();
    return dest;
}

Polynomial operator- (const Polynomial& x, const Polynomial& y) {
    Polynomial negativeY;
    Term* pY = y.head;
    while (pY != nullptr) {
        Term* pTermTemp = new Term;
        pTermTemp->coefficient = -pY->coefficient;
        pTermTemp->exponent = pY->exponent;
        negativeY.insert(pTermTemp);
        pY = pY->next;
    }
    negativeY = x + negativeY;
    negativeY.sort();
    return negativeY;
}

Polynomial operator* (const Polynomial& src, int x) {
    Polynomial dest;
    Term* pSrc = src.head;
    while (pSrc != nullptr) {
        Term* pDest = new Term;
        pDest->coefficient = pSrc->coefficient * x;
        pDest->exponent = pSrc->exponent;
        dest.insert(pDest);
        pSrc = pSrc->next;
    }
    dest.sort();
    return dest;
}

Polynomial operator* (int x, const Polynomial& src) {
    Polynomial dest;
    Term* pSrc = src.head;
    while (pSrc != nullptr) {
        Term* pDest = new Term;
        pDest->coefficient = pSrc->coefficient * x;
        pDest->exponent = pSrc->exponent;
        dest.insert(pDest);
        pSrc = pSrc->next;
    }
    dest.sort();
    return dest;
}

Polynomial operator<< (const Polynomial& src, int x) {
    Polynomial dest;
    Term* pSrc = src.head;
    while (pSrc != nullptr) {
        Term *pDest = new Term;
        pDest->exponent = pSrc->exponent + x;
        pDest->coefficient = pSrc->coefficient;
        dest.insert(pDest);
        pSrc = pSrc->next;
    }
    dest.sort();
    return dest;
}

Polynomial operator* (const Polynomial& x, const Polynomial& y) {
    Polynomial dest;
    Term* pX = x.head;
    while (pX != nullptr) {
        Polynomial temp;
        temp = pX->coefficient * y;
        temp = temp << (pX->exponent);
        dest = temp + dest;
        pX = pX->next;
    }
    dest.sort();
    return dest;
}

Polynomial operator/ (const Polynomial& x, const Polynomial& y) {
    Polynomial dividend = x;
    Polynomial divisor = y;
    Polynomial result;
    Term* pDividend = dividend.head;
    if (dividend.head->exponent < divisor.head->exponent) {
        return dividend;
    }
    while (pDividend != nullptr && pDividend->exponent >= divisor.head->exponent) {
        Term* termResult = new Term;
        termResult->coefficient = pDividend->coefficient / divisor.head->coefficient;
        termResult->exponent = pDividend->exponent - divisor.head->exponent;
        result.insert(termResult);
        dividend = dividend - ((divisor * termResult->coefficient)
                << termResult->exponent);
        pDividend = dividend.head;
    }
    result.sort();
    return result;
}

Polynomial operator% (const Polynomial& x, const Polynomial& y) {
    Polynomial dividend = x;
    Polynomial divisor = y;
    Polynomial result;
    Term* pDividend = dividend.head;
    if (dividend.head->exponent < divisor.head->exponent) {
        return dividend;
    }
    while (pDividend != nullptr && pDividend->exponent >= divisor.head->exponent) {
        Term* termResult = new Term;
        termResult->coefficient = pDividend->coefficient / divisor.head->coefficient;
        termResult->exponent = pDividend->exponent - divisor.head->exponent;
        result.insert(termResult);
        dividend = dividend - ((divisor * termResult->coefficient)
                << termResult->exponent);
        pDividend = dividend.head;
    }
    dividend.sort();
    return dividend;
}
