#include <iostream>
#include <math.h>
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

/* metodo di stampa della frazione in numero razionale con precisione 2 */
void Tfraction::print_float() const {
    float f = roundf(((float)num / den)*100.0)/100.0;
    if (f == 0.0) printf("\x1b[38;5;239m%d\x1b[0m", 0);
    else printf("%2.2f", f);
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
Tfraction Tfraction::operator+(const Tfraction& a) const {
    Tfraction c;

    if (den == a.den) {
        c.den = den;
        c.num = num + a.num;
    } else {
        c.den = mcm(den, a.den);
        c.num = (c.den / den)*num + (c.den / a.den)*a.num;
    }
    c.zero_control(); c.sign_control();
    return c.simplification();
}

/* funzione che prese due strutture Tfraction restituisce un'altra Tfraction defferenza delle precedenti */
Tfraction Tfraction::operator-(const Tfraction& a) const {
    Tfraction c;

    if (den == a.den) {
        c.den = den;
        c.num = num - a.num;
    } else {
        c.den = mcm(den, a.den);
        c.num = (c.den / den)*num - (c.den / a.den)*a.num;
    }
    c.zero_control(); c.sign_control();
    return c.simplification();
}

/* funzione che prese due strutture Tfraction restituisce un'altra Tfraction prodotto delle precedenti */
Tfraction Tfraction::operator*(const Tfraction& a) const {
    Tfraction c;

    c.den = den * a.den;
    c.num = num * a.num;
    c.zero_control(); c.sign_control();
    return c.simplification();
}

Tfraction Tfraction::operator*(float a) const {
    Tfraction c;

    c.num = num * a;
    c.zero_control(); c.sign_control();
    return c.simplification();
}

/* funzione che prese due strutture Tfraction restituisce un'altra Tfraction quoziente delle precedenti */
Tfraction Tfraction::operator/(const Tfraction& a) const {
    Tfraction c;

    c.den = den * a.num;
    c.num = num * a.den;
    c.zero_control(); c.sign_control();
    return c.simplification();
}

/* funzione che presa una struttura Tfraction e un numero intero restituisce un'altra Tfraction alevata alla potenza data */
Tfraction Tfraction::power(int p) const {
    Tfraction c;

    c.num = pow(c.num, p);
    c.den = pow(c.den, p);
    
    c.zero_control(); c.sign_control();
    return c.simplification();
}

/* semplifica la Tfraction data */ 
Tfraction Tfraction::simplification() {
    int abs_num = abs(num), abs_den = abs(den);
    int min = abs_num; 
    if (abs_den < abs_num) min = abs_den;
    for (int i=2; i<=min; i++) {
        if (abs_num % i == 0 && abs_den % i == 0) {
            num /= i; den /= i;
            simplification();
            /* serve per velocizzare l'algoritmo quando ormai non serve più iterare */
            break; 
        }
    }
    return *this;
}

/* prende in input una stringa value e lo converte in un puntatore a Tfraction */
Tfraction str_to_fraction(string value){
    int i = 0;
    string snum;
    while (value[i] != '\0') {

        if (value[i] == '/') {
            ++i; string sden;
            while (value[i] != '\0') {
                sden += value[i];
                ++i;
            }
            return Tfraction(stoi(snum), stoi(sden));
        }

        if (value[i] == '.') { 
            while (value[i] != '\0') {
                snum += value[i];
                ++i;
            }
            return Tfraction(stof(snum));
        }

        snum += value[i];
        ++i;
    }
    return Tfraction(stoi(snum), 1);
}

/* prende in input un puntatore a Tfraction e due valori interi che determinano il massimo numero di spazi dati al numeratore e al denominatore per essere stampati, e stampa Tfraction seguendo questo formato */
void Tfraction::print_format(int max_figures_num, int max_figures_den) const {
    int space_num, space_den;
    if (den == 1) {
        int space = figures(abs(num));
        space_num = space / 2;
        space_den = (space - 1) / 2;
    } else {
        space_num = figures(abs(num));
        space_den = figures(den);
    }
    if (num < 0) ++space_num;

    print_space(max_figures_num - space_num); print(); 
    print_space(max_figures_den - space_den);
    
    cout << " ";
}

void Tfraction::zero_control() {
    if (num == 0) den = 1;
}

void Tfraction::sign_control() {
    if (num < 0 && den < 0) {
        num = (-1) * num;
        den = (-1) * den;
    } else if (den < 0) {
        num = (-1) * num;
        den = (-1) * den;
    }
}
