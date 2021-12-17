#include "all-headers.h"
#include <bits/stdc++.h>
#include <iostream>
using namespace std;

Tfvector::Tfvector() {
    n = 0;
}

Tfvector::Tfvector(int _n) {
    n = _n;
    array = new Fraction[n];
    for (int i = 0; i < n; i++) {
        array[i] = new Tfraction();
    }
}

Tfvector::Tfvector(float *values, int dim) {
    n = dim;
    array = new Fraction[n];
    for(int i = 0; i < n; i++) {
        array[i] = new Tfraction(values[i]);
    }
} 

Tfvector::Tfvector(Fraction* values, int dim) {
    n = dim;
    array = new Fraction[n];
    for(int i = 0; i < n; i++) {
        array[i] = values[i];
    }
}

Tfvector::Tfvector(int _n, int min, int max) {
    n = _n;
    array = new Fraction[n];
    for(int i = 0; i < n; i++){
        array[i] = new Tfraction(
            rand() % (max - min + 1) + min, 
            rand() % (max - min + 1) + min
        );
    }
}

void Tfvector::print() const {
    for (int i = 0; i < n; i++) {
        array[i]->print(); printf(" ");
    }
}

void Tfvector::init() {
    float coe;
    for (int i = 0; i < n; i++) {
        printf("insert number in [%d]: ", i+1); scanf("%f", &coe);
        array[i]->set(coe);
        array[i] = fraction_simplification(array[i]);
    }
}

void Tfvector::multiply(Fraction lambda) {
    for(int i = 0; i < n; i++){
        array[i] = fraction_simplification(
            fraction_product(array[i], lambda)
        );
    }
}

Tfvector::~Tfvector() {
    for (int i = 0; i < n; i++) {
        delete array[i];
    }
    delete[] array;
}

FVector init(FVector m) {
    float coe;
    for (int i = 0; i < m->n; i++) {
        printf("insert number in [%d]: ", i+1); scanf("%f", &coe);
        m->array[i]->set(coe);
        m->array[i] = fraction_simplification(m->array[i]);
    }
    return m;
}

// Fraction get_fraction(string s){
//     string num = "", den = "";
//     bool x = true, y = false;
 
//     // Traverse the floating string
//     for (int i = 0; i < s.size(); ++i) {
//         if (s[i] == '/') { // Check if denominator part exist
//             x = false;
//             y = true;
//             continue;
//         }

//         //get num and den
//         if (x) 
//             num += s[i];
 
//         if (y)
//             den += s[i];
//     }
 
//     // Convert string to integer
//     int numerator = stoi(num);
//     int denominator = 0;
 
//     // Initialize numerator & denominator
//     int numerator = numerator * pow(10, den.size()) + numerator;
 
//     int denominator = pow(10, den.size());
//     int gd = __gcd(numerator, denominator);
    
//     string num = to_string(numerator/gd);
//     string den = to_string(denominator/gd);
//     // to end
// }