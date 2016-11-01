#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H
#include <iostream>

struct Term {
    Term* prev = NULL;
    Term* next = NULL;
    double coefficient = 1.0;
    int exponent = 0;
    Term() {};
    Term(double coefficient, int exponent);
};

class Polynomial {
private:
    Term* head = NULL;
    friend std::ostream& operator<< (std::ostream&, const Polynomial&);
    friend std::istream& operator>> (std::istream&, Polynomial&);
    friend Polynomial operator+ (const Polynomial&, const Polynomial&);
    friend Polynomial operator+ (const Polynomial&, int x);
    friend Polynomial operator+ (int x, const Polynomial&);
    friend Polynomial operator- (const Polynomial&, const Polynomial&);
    friend Polynomial operator* (const Polynomial&, int);
    friend Polynomial operator* (int, const Polynomial&);
    friend Polynomial operator<< (const Polynomial&, int);
    friend Polynomial operator* (const Polynomial&, const Polynomial&);
    friend Polynomial operator/ (const Polynomial&, const Polynomial&);
    friend Polynomial operator% (const Polynomial&, const Polynomial&);


public:
    Polynomial() {};
    Polynomial(const Polynomial&);
    Polynomial& operator=(const Polynomial&);
    Polynomial(Polynomial&&);
    Polynomial& operator=(Polynomial&&);
    ~Polynomial();
    void insert(Term*);
    void remove(Term*);
    void swap(Term*, Term*);
    void sort();
    size_t length() const ;
    double calc(double) const ;
};

std::istream& operator>> (std::istream&, Polynomial&);
std::ostream& operator<< (std::ostream&, const Polynomial&);
Polynomial operator+ (const Polynomial&, const Polynomial&);
Polynomial operator+ (const Polynomial&, int x);
Polynomial operator+ (int x, const Polynomial&);
Polynomial operator- (const Polynomial&, const Polynomial&);
Polynomial operator* (const Polynomial&, int);
Polynomial operator* (int, const Polynomial&);
Polynomial operator<< (const Polynomial&, int);     // move digits
Polynomial operator* (const Polynomial&, const Polynomial&);
Polynomial operator/ (const Polynomial&, const Polynomial&);
Polynomial operator% (const Polynomial&, const Polynomial&);


#endif
