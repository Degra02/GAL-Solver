#include <iostream>
#include "all-headers.h"
using namespace std;

#ifndef __FRACTION_H__
#define __FRACTION_H__

typedef struct Tfraction {
    int num; int den;
    Tfraction();
    Tfraction(int n, int d);
    Tfraction(string n, string d);
    void print() const;
} Tfraction;

typedef Tfraction* Fraction;

Fraction power(Fraction a, int p);
Fraction sum(Fraction a, Fraction b);
Fraction difference(Fraction a, Fraction b);
Fraction product(Fraction a, Fraction b);
Fraction quotient(Fraction a, Fraction b);
Fraction simplification(Fraction a);

int mcm(int a, int b);
int abs(int n);

#endif
