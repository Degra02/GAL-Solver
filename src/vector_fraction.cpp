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
    array = new Tfraction[n];
    for (int i = 0; i < n; i++) {
        array[i] = Tfraction();
    }
}

Tfvector::Tfvector(float *values, int dim) {
    n = dim;
    array = new Tfraction[n];
    for(int i = 0; i < n; i++) {
        array[i] = Tfraction(values[i]);
    }
} 

Tfvector::Tfvector(Fraction values, int dim) {
    n = dim;
    array = new Tfraction[n];
    for(int i = 0; i < n; i++) {
        array[i] = values[i];
    }
}

Tfvector::Tfvector(int _n, int min, int max) {
    n = _n;
    array = new Tfraction[n];
    for(int i = 0; i < n; i++){
        array[i] = Tfraction(
            rand() % (max - min + 1) + min, 
            rand() % (max - min + 1) + min
        );
    }
}

void Tfvector::print() const {
    cout << "(";
    for (int i = 0; i < n; i++) {
        array[i].print();
        if (i != (n - 1)) cout << ", ";
    }
    cout << ")";
}

void Tfvector::init() {
    float coe;
    for (int i = 0; i < n; i++) {
        printf("insert number in [%d]: ", i+1); scanf("%f", &coe);
        array[i].set(coe);
        array[i] = array[i].simplification();
    }
}

Tfvector Tfvector::operator*(const Tfraction& f) const {
    Tfvector v(n);
    for (int i = 0; i < n; ++i){
        array[i] = f * array[i];
    }

    return v;
}

Tfvector::~Tfvector() {
    delete[] array;
}

Tfvector::Tfvector(int dim, string _name){
    n = dim;
    array = new Tfraction[n];
    for(int i = 0; i < n; i++){
        array[i] = Tfraction();
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
        v->array[i] = v->array[i].simplification();
    }
    cout << endl;
    return v;
}

void Tfvector::print(const Tfvector& v) const {
    cout << "Name: " << "\x1b[38;5;50m" << v.name << "\x1b[0m = ";
    cout << endl << endl;
    cout << "   "; v.print();
    cout << endl << endl;
}

Tfvector Tfvector::copy() const {
    Tfvector b(n);
    for(int i = 0; i < n; ++i){
        b.array[i] = array[i];
    }
    return b;
}

bool fvector_same_dimension(FVector a, FVector b){
    return (a->n == b->n);
}

Tfvector Tfvector::operator+(const Tfvector& b) const {
    Tfvector res(n);
    for(int i = 0; i < n; i++){
        res.array[i] = array[i] + b.array[i];
    }
    return res;
}

Tfvector Tfvector::operator-(const Tfvector& b) const {
    Tfvector res(n);
    for(int i = 0; i < n; i++){
        res.array[i] = array[i] - b.array[i];
    }
    return res;
}

Tfraction Tfvector::norm_noroot() const {
    Tfraction res = array[0].power(2);
    for(int i = 1; i < n; i++){
        res = res + array[i].power(2);
    }
    return res;
}

float Tfvector::float_norm() const {
    Tfraction res = array[0].power(2);
    for(int i = 1; i < n; i++){
        res = res + array[i].power(2);
    }
    return sqrt( (float)res.num / (float)res.den );
}

string fvector_norm_print(Fraction a){
    if(a->num == 0){
        return "0";
    } else if(a->den == 1){
        return "sqrt( " + to_string(a->num) + " )";
    }
    return "sqrt( " + to_string(a->num) + "/" + to_string(a->den) + " )";
}

Tfraction Tfvector::operator*(const Tfvector& b) const {
    Tfraction res = array[0] + b.array[0];
    for(int i = 1; i < n; i++){
        res = res + (array[i] * b.array[i]);
    }
    return res;
}

FVector Tfvector::cross_product(const Tfvector& b) const {
    if((n == 3) && (b.n == 3)){
        FVector res = new Tfvector(3);
        res->array[0] = (array[1] * b.array[3]) + (array[2] * b.array[1]);
        res->array[1] = (array[2] * b.array[0]) + (array[0] * b.array[2]);
        res->array[2] = (array[0] * b.array[1]) + (array[1] * b.array[0]);
        return res;
    }
    return NULL;
}

float Tfvector::angle(const Tfvector& b) const{
    Tfraction res = *this * b;
    float val = (float)res.num / (float)res.den;
    return acos( val / ((*this).float_norm() * b.float_norm()));
}