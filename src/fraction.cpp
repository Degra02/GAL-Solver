#include <iostream>
#include "all-headers.h"
using namespace std;

// Methods

/* costruttore di default */
Tfraction::Tfraction() {
    num = 0; den = 1;
}

/* costruttore dati due numeri interi, uno diventa numeratore e l'altro denominatore */
Tfraction::Tfraction(int n, int d) {
    num = n;
    if (d != 0) den = d;
    else den = 1;
    if (n >= 0 && d < 0) {
        num = -n;
        den = -d;
    }
}

/* costruttore dato un numero decimale lo trasforma in frazione richiamando il metodo set */
Tfraction::Tfraction(float n) {
    set(n);
}

/* costruttore date due stringhe li convete in numeratore e denominatore */
Tfraction::Tfraction(string n, string d) {
    num = stoi(n); den = stoi(d);
}

/* metodo di stampa della frazione */
void Tfraction::print() const {
    if (den == 1 || num == 0) printf("%d", num);
    else printf("%d/%d", num, den);
}

/* metodo che prende un numero decimale e con arrotondamento 2 cifre dopo la virgola lo 
trasforma in frazione */
void Tfraction::set(float n) {
    int m = 1; float f = n;
    while (f > 0) {
        m *= 10; 
        f = n; f -= m; 
    }
    m *= 10;
    num = round(n*m);
    if (num == 0) den = 1;
    else den = m;
}

// Functions

/* funzione che prese due strutture Tfraction restituisce un'altra Tfraction 
somma delle precedenti */
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

/* funzione che prese due strutture Tfraction restituisce un'altra Tfraction 
defferenza delle precedenti */
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

/* funzione che prese due strutture Tfraction restituisce un'altra Tfraction 
prodotto delle precedenti */
Fraction fraction_product(Fraction a, Fraction b) {
    Fraction c = new Tfraction();

    c->den = a->den * b->den;
    c->num = a->num * b->num;
    return fraction_simplification(c);
}

/* funzione che prese due strutture Tfraction restituisce un'altra Tfraction 
quoziente delle precedenti */
Fraction fraction_quotient(Fraction a, Fraction b) {
    Fraction c = new Tfraction();

    c->den = a->den * b->num;
    c->num = a->num * b->den;
    return fraction_simplification(c);
}

/* funzione che presa una struttura Tfraction e un numero intero restituisce un'altra
Tfraction alevata alla potenza data */
Fraction fraction_power(Fraction a, int p) {
    Fraction c = new Tfraction(1, 1);

    for (int i=0; i<p; i++) {
        c->num *= a->num;
        c->den *= a->den;
    }
    return fraction_simplification(c);
}

/* semplifica la Tfraction data */ 
Fraction fraction_simplification(Fraction a) {
    int abs_num = abs(a->num), abs_den = abs(a->den);
    int min = abs_num; 
    if (abs_den < abs_num) min = abs_den;
    for (int i=2; i<=min; i++) {
        if (abs_num % i == 0 && abs_den % i == 0) {
            a->num /= i; a->den /= i;
            fraction_simplification(a); 
            break; /*serve per velocizzare l'algoritmo quando ormai non serve più iterare*/
        }
    }
    return a;
}

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

Fraction str_to_fraction(string value){
    int i = 0;
    string snum, sden;
    while(value[i] != '/'){
        snum += value[i];
        i++;
    }
    i++;
    while(value[i] != '\0'){
        sden += value[i];
        i++;
    }
    return new Tfraction(stoi(snum), stoi(sden));
}
