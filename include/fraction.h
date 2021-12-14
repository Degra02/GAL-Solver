#include <iostream>
using namespace std;

#ifndef __FRACTION_H__
#define __FRACTION_H__

typedef struct Tfraction {
    int num; int den;
    Tfraction();
    Tfraction(float n);
    Tfraction(int n, int d);
    Tfraction(string n, string d);
    void print() const;
    void set(float n); 
} Tfraction;

typedef Tfraction* Fraction;

Fraction fraction_power(Fraction a, int p);
Fraction fraction_sum(Fraction a, Fraction b);
Fraction fraction_difference(Fraction a, Fraction b);
Fraction fraction_product(Fraction a, Fraction b);
Fraction fraction_quotient(Fraction a, Fraction b);
Fraction fraction_simplification(Fraction a);

int mcm(int a, int b);
int abs(int n);

#endif
