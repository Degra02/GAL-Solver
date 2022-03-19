#include <iostream>
#ifndef __FRACTION_H__
#define __FRACTION_H__
using namespace std;

typedef struct Tfraction{
    int num; int den;

    Tfraction();
    Tfraction(float n);
    Tfraction(int n, int d);
    Tfraction(string n, string d);
    void print() const;
    void print_float() const;
    void set(float n); 
}Tfraction;

typedef Tfraction* Fraction;

Fraction fraction_power(Fraction a, int p);
Fraction fraction_sum(Fraction a, Fraction b);
Fraction fraction_difference(Fraction a, Fraction b);
Fraction fraction_product(Fraction a, Fraction b);
Fraction fraction_quotient(Fraction a, Fraction b);
Fraction fraction_simplification(Fraction a);
Fraction fraction_copy(Fraction a);
Fraction str_to_fraction(string value);
void print_format_fraction(Fraction f, int max_figures_num, int max_figures_den);
void zero_control(Fraction f);
void sign_control(Fraction f);
void control(Fraction f);

#endif
