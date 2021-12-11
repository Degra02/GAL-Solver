#include <iostream>
#include "all-headers.h"
using namespace std;

#ifndef __FRACTION_H__
#define __FRACTION_H__

typedef struct Tfraction {
    int num;
    int den;

    Tfraction(){
        num = 0;
        den = 1;
    }

    Tfraction(int n, int d){
        num = n;
        if (d != 0) den = d;
    }

    Tfraction(string n, string d){
        num = stoi(n);
        den = stoi(d);
    }

    void print() const{
        if (den == 1) printf("%d\n", num);
        else printf("%d/%d\n", num, den);
    }

}Tfraction;

typedef Tfraction* Fraction;

int mcm(int a, int b);
int abs(int n);

Fraction power(Fraction a, int p);
Fraction sum(Fraction a, Fraction b);
Fraction difference(Fraction a, Fraction b);
Fraction product(Fraction a, Fraction b);
Fraction quotient(Fraction a, Fraction b);
Fraction simplification(Fraction a);

#endif
