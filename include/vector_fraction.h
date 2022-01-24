#include "all-headers.h"
#include <iostream>
#ifndef __VECTOR_FRACTION_H__
#define __VECTOR_FRACTION_H__
using namespace std;

typedef struct Tfvector { 
    Fraction array; int n;
    string name;

    Tfvector();
    Tfvector(int _n);
    Tfvector(float *values, int dim);
    Tfvector(int dim, string _name);
    Tfvector(Fraction values, int dim);
    Tfvector(int _n, int min, int max);
    ~Tfvector();
    void print() const;
    void init();
    Tfvector copy() const;
    Tfvector operator+(const Tfvector& b) const;
    Tfvector operator-(const Tfvector& b) const;

    // aka product_with_scalar
   Tfvector operator*(const Tfraction& b) const;

    // aka scalar_product
    Tfraction operator*(const Tfvector& b) const;
    Tfvector* cross_product(const Tfvector& b) const;
    bool same_dimension(const Tfvector& b) const;
    Tfraction norm_noroot() const;
    float float_norm() const;
    float angle(const Tfvector& b) const;
    void print(const Tfvector& v) const;
} Tfvector;

typedef Tfvector* FVector;

FVector init_fvector(string name);

string fvector_norm_print(Fraction a);

#endif