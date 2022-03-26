#include "all-headers.h"
#include <bits/stdc++.h>
#include <locale.h>
#include <iostream>
using namespace std;

Tn::Tn() {
    number = 1; 
    sqrt = 1;
}

Tn::Tn(int _n) {
    number = _n;
    sqrt = 1;
}

Tn::Tn(int _n, int _s) {
    number = _n; 
    sqrt = _s;
}

void Tn::print() const {
    if (number != 1 && sqrt != 1) printf("%d\x1b[38;5;197msqrt\x1b[0m(%d)", number, sqrt);
    else if (sqrt != 1) printf("\x1b[38;5;197msqrt\x1b[0m(%d)", sqrt);
    else printf("%d", number);
}

Tscalar::Tscalar() {
    num = Tn();
    den = Tn();
}

Tscalar::Tscalar(Tn n, Tn d) {
    num = n;
    den = d;
}

void Tscalar::print() const {
    if (den.number == 1 && den.sqrt == 1 && num.number == 1 && num.sqrt == 1);
    else if (den.number == 1 && den.sqrt == 1) num.print();
    else { num.print(); printf("/"); den.print(); }
}

Tfvector::Tfvector() {
    n = 0;
    scl = Tscalar();
}

Tfvector::Tfvector(int _n) {
    n = _n;
    scl = Tscalar();
    array = new Fraction[n];
    for (int i = 0; i < n; i++) {
        array[i] = new Tfraction();
    }
}

Tfvector::Tfvector(float *values, int dim) {
    n = dim;
    scl = Tscalar();
    array = new Fraction[n];
    for(int i = 0; i < n; i++) {
        array[i] = new Tfraction(values[i]);
    }
} 

Tfvector::Tfvector(Fraction* values, int dim) {
    n = dim;
    scl = Tscalar();
    array = new Fraction[n];
    for(int i = 0; i < n; i++) {
        array[i] = values[i];
    }
}

Tfvector::Tfvector(int _n, int min, int max) {
    n = _n;
    scl = Tscalar();
    array = new Fraction[n];
    for(int i = 0; i < n; i++){
        array[i] = new Tfraction(
            rand() % (max - min + 1) + min, 
            rand() % (max - min + 1) + min
        );
    }
}

void Tfvector::print() const {
    scl.print();
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

Vector init_fvector(string name){
    int n; string value;
    cout << "dimension= "; cin >> n; 
    cout << endl; Vector v = new Tfvector(n, name);
    for(int i = 0; i < n; i++){
        cout << "   ";
        cin >> value;
        v->array[i] = str_to_fraction(value);
        v->array[i] = fraction_simplification(v->array[i]);
    }
    cout << endl;
    return v;
}

Vector init_fvector_system(string name, int n){
    string value; cout << endl; Vector v = new Tfvector(n, name);
    for(int i = 0; i < n; i++){
        cout << "   ";
        cin >> value;
        v->array[i] = str_to_fraction(value);
        v->array[i] = fraction_simplification(v->array[i]);
    }
    cout << endl;
    return v;
}

void print_fvector(Vector v){
    cout << "Name: " << "\x1b[38;5;50m" << v->name << "\x1b[0m = ";
    cout << "   "; v->print();
    cout << endl << endl;
}

Vector fraction_vector_copy(Vector a){
    Vector b = new Tfvector(a->n);
    int dim = a->n;
    for(int i = 0; i < dim; ++i){
        b->array[i] = a->array[i];
    }
    return b;
}

bool fvector_same_dimension(Vector a, Vector b){
    return (a->n == b->n);
}

Vector fvector_sum(Vector a, Vector b){
    int n = a->n; Vector res = new Tfvector(n);
    for(int i = 0; i < n; i++){
        res->array[i] = fraction_sum(a->array[i], b->array[i]);
    }
    return res;
}

Vector fvector_difference(Vector a, Vector b){
    int n = a->n; Vector res = new Tfvector(n);
    for(int i = 0; i < n; i++){
        res->array[i] = fraction_difference(a->array[i], b->array[i]);
    }
    return res;
}

Fraction fvector_norm_noroot(Vector a){
    int n = a->n; Fraction res = fraction_power(a->array[0], 2);
    for(int i = 1; i < n; i++){
        res = fraction_sum(res, fraction_power(a->array[i], 2));
    }
    return res;
}

float fvector_float_norm(Vector a){
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

Fraction fvector_scalar_product(Vector a, Vector b){
    int n = a->n; Fraction res = fraction_product(a->array[0], b->array[0]);
    for(int i = 1; i < n; i++){
        res = fraction_sum(res, fraction_product(a->array[i], b->array[i]));
    }
    return res;
}

Vector fvector_cross_product(Vector a, Vector b){
    if((a->n == 3) && (b->n == 3)){
        Vector res = new Tfvector(3);
        res->array[0] = fraction_difference(fraction_product(a->array[1], b->array[2]), fraction_product(a->array[2], b->array[1]));
        res->array[1] = fraction_difference(fraction_product(a->array[2], b->array[0]), fraction_product(a->array[0], b->array[2]));
        res->array[2] = fraction_difference(fraction_product(a->array[0], b->array[1]), fraction_product(a->array[1], b->array[0]));
        return res;
    }
    return NULL;
}

float fvector_angle(Vector a, Vector b){
    Fraction res = fvector_scalar_product(a, b);
    float val = (float)res->num / (float)res->den;
    return acos( val / (fvector_float_norm(a) * fvector_float_norm(b)));
}

Vector fvector_product_with_scalar(Vector v, Fraction f) {
    Vector res = new Tfvector(v->n);
    for (int i = 0; i < v->n; ++i){
        res->array[i] = fraction_product(f, v->array[i]);
    }

    return res;
}

Vector fvector_normalization(Vector v) {
    Vector vn = v;
    Fraction f = fvector_norm_noroot(v);
    Tscalar sn = Tscalar(Tn(1, f->den), Tn(1, f->num));
    vn->scl = sn;
    return vn;
}