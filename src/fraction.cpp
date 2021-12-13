#include <iostream>
#include "all-headers.h"
using namespace std;

Tfraction::Tfraction() {
    num = 0; den = 1;
}

Tfraction::Tfraction(int n, int d) {
    num = n;
    if (d != 0) den = d;
    else d = 1;
}

Tfraction::Tfraction(float n) {
    int m = 1;
    float f = n;
    while (f > 0) {
        m *= 10; 
        f = n; f -= m; 
    }
    m *= 10;

    num = round(n*m);
    den = m;
}

Tfraction::Tfraction(string n, string d) {
    num = stoi(n); den = stoi(d);
}

void Tfraction::print() const {
    if (den == 1) printf("%d", num);
    else printf("%d/%d", num, den);
}

Fraction fraction_sum(Fraction a, Fraction b) {
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

Fraction fraction_difference(Fraction a, Fraction b) {
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

Fraction fraction_product(Fraction a, Fraction b) {
    Fraction c = new Tfraction();

    c->den = a->den * b->den;
    c->num = a->num * b->num;
    return c;
}

Fraction fraction_quotient(Fraction a, Fraction b) {
    Fraction c = new Tfraction();

    c->den = a->den * b->num;
    c->num = a->num * b->den;
    return c;
}

Fraction fraction_power(Fraction a, int p) {
    Fraction c = new Tfraction(1, 1);

    for (int i=0; i<p; i++) {
        c->num *= a->num;
        c->den *= a->den;
    }
    return c;
}

Fraction fraction_simplification(Fraction a) {
    int abs_num = abs(a->num), abs_den = abs(a->den);
    int min = abs_num; 
    if (abs_den < abs_num) min = abs_den;
    for (int i=2; i<=min; i++) {
        if (abs_num % i == 0 && abs_den % i == 0) {
            a->num /= i; a->den /= i;
            fraction_simplification(a);
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

int abs(int n) {
    if (n >= 0) return n;
    return -n;
}
