#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H
#include <iostream>

struct Term {
    Term* prev = NULL;
    Term* next = NULL;
    int exponent = 0;
    int coefficient = 1;
    Term() {};
    Term(int coefficient, int exponent);
};

class Polynomial {
private:
    Term* headPointer = NULL;
    friend std::ostream& operator<< (std::ostream&, const Polynomial&);
    friend std::istream& operator>> (std::istream&, Polynomial&);
    friend Polynomial operator+ (const Polynomial&, const Polynomial&);
    friend Polynomial operator- (const Polynomial&, const Polynomial&);
public:
    Polynomial() {};
    Polynomial(const Polynomial&) = delete;         // for the sake of the non-copyable
    Polynomial& operator=(const Polynomial&) = delete;
    Polynomial(Polynomial&&);
    ~Polynomial();
    Polynomial& operator=(Polynomial&&);
    Term* head();
    void insert(Term*);
    size_t length();
    void swap(Term*, Term*);
    double calc(double);
};

std::istream& operator>> (std::istream&, Polynomial&);
std::ostream& operator<< (std::ostream&, const Polynomial&);
Polynomial operator+ (const Polynomial&, const Polynomial&);
Polynomial operator- (const Polynomial&, const Polynomial&);

#endif
