#include <iostream>
#include "all-headers.h"
using namespace std;

// Methods

/* default constructor */
Tfraction::Tfraction(){
    num = 0; den = 1;
}

/* numerator and denominator constructor */
Tfraction::Tfraction(int n, int d){
    num = n;
    if(d != 0) den = d;
    else den = 1;
    // zero and sign control
    if(num == 0) den = 1;
    else if(num < 0 && den < 0){
        num = (-1) * num;
        den = (-1) * den;
    } else if(den < 0){
        num = (-1) * num;
        den = (-1) * den;
    }
}

/* constructor that given a float number turns it into a fraction */
Tfraction::Tfraction(float n){
    set(n);
}

/* constructor that turns two strings in numerator and denominator */
Tfraction::Tfraction(string n, string d){
    num = stoi(n); den = stoi(d);
}

/* fraction print method */
void Tfraction::print() const {
    if(den == 1){
        if(num == 0) printf("\x1b[38;5;239m%d\x1b[0m", 0);
        else printf("%d", num);
    }
    else printf("%d/%d", num, den);
}

/* print method of a function into a float approximated to 2 decimal digits */
void Tfraction::print_float() const {
    float f = roundf(((float)num / den)*100.0)/100.0;
    if(f == 0.0) printf("\x1b[38;5;239m%d\x1b[0m", 0);
    else printf("%2.2f", f);
}

/* turns a two decimal digits float number into a fraction*/
void Tfraction::set(float n){
    float f = n;
    int m = 1;
    while(f > 0){
        m = m * 10; 
        f = n; 
        f = f - m; 
    }
    m = m * 10; num = round(n * m);
    if (num == 0) den = 1;
    else den = m;
}

// Functions

/* sum of two fraction */
Fraction fraction_sum(Fraction a, Fraction b) {
    Fraction c = new Tfraction();
    if(a->den == b->den){
        c->den = a->den;
        c->num = a->num + b->num;
    } else {
        c->den = mcm(a->den, b->den);
        c->num = (c->den / a->den)*a->num + (c->den / b->den)*b->num;
    }
    control(c); return fraction_simplification(c);
}

/* difference of two fractions */
Fraction fraction_difference(Fraction a, Fraction b){
    Fraction c = new Tfraction();  
    if(a->den == b->den){
        c->den = a->den;
        c->num = a->num - b->num;
    } else {
        c->den = mcm(a->den, b->den);
        c->num = (c->den / a->den)*a->num - (c->den / b->den)*b->num;
    }
    control(c); return fraction_simplification(c);
}

/* product of two fractions */
Fraction fraction_product(Fraction a, Fraction b){
    Fraction c = new Tfraction(); 
    c->den = a->den * b->den;
    c->num = a->num * b->num;
    control(c); return fraction_simplification(c);
}

/* quotient of two fractions */
Fraction fraction_quotient(Fraction a, Fraction b){
    Fraction c = new Tfraction();
    c->den = a->den * b->num;
    c->num = a->num * b->den;
    control(c); return fraction_simplification(c);
}

/* returns the fraction to the power of the int parameter */
Fraction fraction_power(Fraction a, int p) {
    Fraction c = new Tfraction(1, 1);
    for(int i = 0; i < p; i++){
        c->num *= a->num;
        c->den *= a->den;
    }
    control(c); return fraction_simplification(c);
}

/* simplifies the given fraction */ 
Fraction fraction_simplification(Fraction a){
    int abs_num = abs(a->num), abs_den = abs(a->den);
    int min = abs_num; 
    if(abs_den < abs_num) min = abs_den;
    for(int i = 2; i <= min; i++){
        if(abs_num % i == 0 && abs_den % i == 0){
            a->num /= i; a->den /= i;
            fraction_simplification(a); 
            /* serve per velocizzare l'algoritmo quando ormai non serve più iterare */
            break; 
        }
    }
    return a;
}

/* turns a string value into a fraction */
Fraction str_to_fraction(string value){
    int i = 0; string snum;
    while(value[i] != '\0'){
        if(value[i] == '/'){
            ++i; string sden;
            while(value[i] != '\0'){ sden += value[i]; ++i; }
            return new Tfraction(stoi(snum), stoi(sden));
        }
        if(value[i] == '.'){ 
            while(value[i] != '\0'){ snum += value[i]; ++i; }
            return new Tfraction(stof(snum));
        }
        snum += value[i];
        ++i;
    }
    return new Tfraction(stoi(snum), 1);
}

/* takes two integer values and a fraction that set the 
max n° of spaces given to the numerator and the denominator to be printed, 
and prints the fraction given this format*/
void print_format_fraction(Fraction f, int max_figures_num, int max_figures_den){
    int space_num, space_den;
    if(f->den == 1){
        int space = figures(abs(f->num));
        space_num = space / 2;
        space_den = (space - 1) / 2;
    } else {
        space_num = figures(abs(f->num));
        space_den = figures(f->den);
    }
    if(f->num < 0) ++space_num;
    print_space(max_figures_num - space_num); f->print(); 
    print_space(max_figures_den - space_den);
    cout << " ";
}

/* if num == 0, then the den == 1 to avoid quotient errors */
void zero_control(Fraction f){
    if(f->num == 0) f->den = 1;
}

/* checks the sign of a given fraction */
void sign_control(Fraction f){
    if(f->num < 0 && f->den < 0){
        f->num = (-1) * f->num;
        f->den = (-1) * f->den;
    } else if (f->den < 0) {
        f->num = (-1) * f->num;
        f->den = (-1) * f->den;
    }
}

/* checks both zero presence or negative values */
void control(Fraction f){
    zero_control(f);
    sign_control(f);
}

/* returns a copy of the given fraction */
Fraction fraction_copy(Fraction a){
    return new Tfraction(a->num, a->den);
}
