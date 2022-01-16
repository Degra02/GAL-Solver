#include <iostream>
#ifndef __FRACTION_H__
#define __FRACTION_H__
using namespace std;

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

/* operazioni base delle frazioni */
Fraction fraction_power(Fraction a, int p);
Fraction fraction_sum(Fraction a, Fraction b);
Fraction fraction_difference(Fraction a, Fraction b);
Fraction fraction_product(Fraction a, Fraction b);
Fraction fraction_quotient(Fraction a, Fraction b);
Fraction fraction_simplification(Fraction a);

Fraction str_to_fraction(string value);
void print_format_fraction(Fraction f, int max_figures_num, int max_figures_den);

#endif
