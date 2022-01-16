#include <iostream>
#include "all-headers.h"

using namespace std;

/* presi due numeri interi restituisce il minimo comune divisore */
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

/* restituisce il modulo di un numero intero */
int abs(int n) {
    if (n >= 0) return n;
    return -n;
}

/* prende in input un valore intero e restituisce il suo numero di cifre */ 
int figures(int n) {
    int c = 1, counter = 0;
    do {
        ++counter; c *= 10;
    } while (n / c >= 1);

    return counter;
}

/* prende in input un valore intero che corrisponde al numero di spazi che stampa */
void print_space(int dim) {
    for (int i = 0; i < dim; ++i) cout << " ";
}