#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include "all-headers.h"
using namespace std;

Fraction sum(Fraction a, Fraction b) {
    Fraction c = new Tfraction();

    if (a->den == b->den) {
        c->den = a->den;
        c->num = a->num + b->num;
    } else {
        c->den = mcm(a->den, b->den);
        c->num = (c->den / a->den)*a->num + (c->den / b->den)*b->num;
    }
    return c;
}

Fraction difference(Fraction a, Fraction b) {
    Fraction c = new Tfraction(); 

    if (a->den == b->den) {
        c->den = a->den;
        c->num = a->num - b->num;
    } else {
        c->den = mcm(a->den, b->den);
        c->num = (c->den / a->den)*a->num - (c->den / b->den)*b->num;
    }
    return c;
}

Fraction product(Fraction a, Fraction b) {
    Fraction c = new Tfraction();

    c->den = a->den * b->den;
    c->num = a->num * b->num;
    return c;
}

Fraction quotient(Fraction a, Fraction b) {
    Fraction c = new Tfraction();

    c->den = a->den * b->num;
    c->num = a->num * b->den;
    return c;
}

Fraction power(Fraction a, int p) {
    Fraction c = new Tfraction(1, 1);

    for (int i=0; i<p; i++) {
        c->num *= a->num;
        c->den *= a->den;
    }
    return c;
}

Fraction simplification(Fraction a) {
    int min = a->num; 
    if (a->den < a->num) min = a->den;
    for (int i=2; i<=min; i++) {
        if (a->num % i == 0 && a->den % i == 0) {
            a->num /= i; a->den /= i;
            simplification(a);
            /*serve per velocizzare l'algoritmo quando ormai non serve più iterare*/
            break; 
        }
    }
    return a;
}

int mcm(int a, int b) {
    int max = a, c;
    if (a < b) max = b;
    if (max % a == 0 && max % b == 0) return b;

    c = max;
    do {
        c += max;
    } while (c % b != 0 || c % a != 0);

    return c;
}
