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
    void print_float() const;
    void set(float n); 
    Tfraction operator+(const Tfraction& a) const;
    Tfraction operator-(const Tfraction& a) const;
    Tfraction operator*(const Tfraction& a) const;
    Tfraction operator*(float a) const;
    Tfraction operator/(const Tfraction& a) const;
    Tfraction power(int p) const;
    Tfraction simplification();
    void print_format(int max_figures_num, int max_figures_den) const;
    void zero_control();
    void sign_control();
} Tfraction;

typedef Tfraction* Fraction;

Tfraction str_to_fraction(string value);

#endif
