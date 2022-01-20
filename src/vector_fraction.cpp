#include "all-headers.h"
#include <bits/stdc++.h>
#include <locale.h>
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
    cout << "(";
    for (int i = 0; i < n; i++) {
        array[i]->print();
        if (i != (n - 1)) cout << ", ";
    }
    cout << ")";
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
        array[i] = fraction_product(array[i], lambda);
    }
}

Tfvector::~Tfvector() {
    for (int i = 0; i < n; i++) {
        delete array[i];
    }
    delete[] array;
}

Tfvector::Tfvector(int dim, string _name){
    n = dim;
    array = new Fraction[n];
    for(int i = 0; i < n; i++){
        array[i] = new Tfraction();
    }
    name = _name;
}

FVector init_fvector(string name){
    int n; string value;
    cout << "dimension= "; cin >> n; 
    cout << endl; FVector v = new Tfvector(n, name);
    for(int i = 0; i < n; i++){
        cout << "   ";
        cin >> value;
        v->array[i] = str_to_fraction(value);
        v->array[i] = fraction_simplification(v->array[i]);
    }
    cout << endl;
    return v;
}

void print_fvector(FVector v){
    cout << "Name: " << "\x1b[38;5;50m" << v->name << "\x1b[0m = ";
    cout << endl << endl;
    cout << "   "; v->print();
    cout << endl << endl;
}

FVector fraction_vector_copy(FVector a){
    FVector b = new Tfvector(a->n);
    int dim = a->n;
    for(int i = 0; i < dim; ++i){
        b->array[i] = a->array[i];
    }
    return b;
}

bool fvector_same_dimension(FVector a, FVector b){
    return (a->n == b->n);
}

FVector fvector_sum(FVector a, FVector b){
    int n = a->n; FVector res = new Tfvector(n);
    for(int i = 0; i < n; i++){
        res->array[i] = fraction_sum(a->array[i], b->array[i]);
    }
    return res;
}

FVector fvector_difference(FVector a, FVector b){
    int n = a->n; FVector res = new Tfvector(n);
    for(int i = 0; i < n; i++){
        res->array[i] = fraction_difference(a->array[i], b->array[i]);
    }
    return res;
}

Fraction fvector_norm_noroot(FVector a){
    int n = a->n; Fraction res = fraction_power(a->array[0], 2);
    for(int i = 1; i < n; i++){
        res = fraction_sum(res, fraction_power(a->array[i], 2));
    }
    return res;
}

float fvector_float_norm(FVector a){
    int n = a->n; Fraction res = fraction_power(a->array[0], 2);
    for(int i = 1; i < n; i++){
        res = fraction_sum(res, fraction_power(a->array[i], 2));
    }
    return sqrt( (float)res->num / (float)res->den );
}

string fvector_norm_print(Fraction a){
    if(a->num == 0){
        return "0";
    } else if(a->den == 1){
        return "sqrt( " + to_string(a->num) + " )";
    }
    return "sqrt( " + to_string(a->num) + "/" + to_string(a->den) + " )";
}

Fraction fvector_scalar_product(FVector a, FVector b){
    int n = a->n; Fraction res = fraction_sum(a->array[0], b->array[0]);
    for(int i = 1; i < n; i++){
        res = fraction_sum(res, fraction_product(a->array[i], b->array[i]));
    }
    return res;
}

float fvector_angle(FVector a, FVector b){
    Fraction res = fvector_scalar_product(a, b);
    float val = (float)res->num / (float)res->den;
    return acos( val / (fvector_float_norm(a) * fvector_float_norm(b)));
}