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

int mcm(int a, int b) {
    int max = a, c;
    if (a < b) max = b;
    if (max % a == 0 && max % b == 0) return b;

    c = max;
    do {
        ++c;
    } while (c % b != 0 || c % a != 0);

    return c;
}