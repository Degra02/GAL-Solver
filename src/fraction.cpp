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
    if (n > 0 && d < 0) {
        num = -n;
        den = -d;
    }
    if (n == 0) d = 1;
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
    if (den == 1) {
        if (num == 0) printf("\x1b[38;5;239m%d\x1b[0m", 0);
        else printf("%d", num);
    }
    else printf("%d/%d", num, den);
}

/* metodo che prende un numero decimale e con arrotondamento 2 cifre dopo la virgola lo trasforma in frazione */
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

/* funzione che prese due strutture Tfraction restituisce un'altra Tfraction somma delle precedenti */
Fraction fraction_sum(Fraction a, Fraction b) {
    Fraction c = new Tfraction();

    if (a->den == b->den) {
        c->den = a->den;
        c->num = a->num + b->num;
    } else {
        c->den = mcm(a->den, b->den);
        c->num = (c->den / a->den)*a->num + (c->den / b->den)*b->num;
    }
    zero_control(c);
    return fraction_simplification(c);
}

/* funzione che prese due strutture Tfraction restituisce un'altra Tfraction defferenza delle precedenti */
Fraction fraction_difference(Fraction a, Fraction b) {
    Fraction c = new Tfraction(); 

    if (a->den == b->den) {
        c->den = a->den;
        c->num = a->num - b->num;
    } else {
        c->den = mcm(a->den, b->den);
        c->num = (c->den / a->den)*a->num - (c->den / b->den)*b->num;
    }
    zero_control(c);
    return fraction_simplification(c);
}

/* funzione che prese due strutture Tfraction restituisce un'altra Tfraction prodotto delle precedenti */
Fraction fraction_product(Fraction a, Fraction b) {
    Fraction c = new Tfraction();

    c->den = a->den * b->den;
    c->num = a->num * b->num;
    zero_control(c);
    return fraction_simplification(c);
}

/* funzione che prese due strutture Tfraction restituisce un'altra Tfraction quoziente delle precedenti */
Fraction fraction_quotient(Fraction a, Fraction b) {
    Fraction c = new Tfraction();

    c->den = a->den * b->num;
    c->num = a->num * b->den;
    zero_control(c);
    return fraction_simplification(c);
}

/* funzione che presa una struttura Tfraction e un numero intero restituisce un'altra Tfraction alevata alla potenza data */
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
            /* serve per velocizzare l'algoritmo quando ormai non serve più iterare */
            break; 
        }
    }
    return a;
}

/* prende in input una stringa value e lo converte in un puntatore a Tfraction */
Fraction str_to_fraction(string value){
    int i = 0;
    string snum;
    while (value[i] != '\0') {

        if (value[i] == '/') {
            ++i; string sden;
            while (value[i] != '\0') {
                sden += value[i];
                ++i;
            }
            return new Tfraction(stoi(snum), stoi(sden));
        }

        if (value[i] == '.') { 
            while (value[i] != '\0') {
                snum += value[i];
                ++i;
            }
            return new Tfraction(stof(snum));
        }

        snum += value[i];
        ++i;
    }
    return new Tfraction(stoi(snum), 1);
}

/* prende in input un puntatore a Tfraction e due valori interi che determinano il massimo numero di spazi dati al numeratore e al denominatore per essere stampati, e stampa Tfraction seguendo questo formato */
void print_format_fraction(Fraction f, int max_figures_num, int max_figures_den) {
    int space_num, space_den;
    if (f->den == 1) {
        int space = figures(abs(f->num));
        space_num = space / 2;
        space_den = (space - 1) / 2;
    } else {
        space_num = figures(abs(f->num));
        space_den = figures(f->den);
    }
    if (f->num < 0) ++space_num;

    print_space(max_figures_num - space_num); f->print(); 
    print_space(max_figures_den - space_den);
    
    cout << " ";
}

void zero_control(Fraction f) {
    if (f->num == 0) f->den = 1;
}
