#include "all-headers.h"
#include <iostream>
#ifndef __VECTOR_H__
#define __VECTOR_H__
using namespace std;

typedef struct Tn {
    int number;
    int sqrt;

    Tn();
    Tn(int _n);
    Tn(int _n, int _s);
    void print() const;
} Tn;

typedef struct Tscalar {
    Tn num;
    Tn den;

    Tscalar();
    Tscalar(Tn n, Tn d);
    void print() const;
} Tscalar;

typedef struct Tfvector { 
    Fraction *array; int n;
    string name;
    Tscalar scl;

    Tfvector();
    Tfvector(int _n);
    Tfvector(float *values, int dim);
    Tfvector(int dim, string _name);
    Tfvector(Fraction* values, int dim);
    Tfvector(int _n, int min, int max);
    ~Tfvector();
    void print() const;
    void init();
    void multiply(Fraction lambda);
} Tfvector;

typedef Tfvector* Vector;

Vector init_fvector(string name);
Vector init_fvector_system(string name, int n);
void print_fvector(Vector v);

Vector fraction_vector_copy(Vector a);
bool fvector_same_dimension(Vector a, Vector b);
Vector fvector_sum(Vector a, Vector b);
Vector fvector_difference(Vector a, Vector b);
Vector fvector_product_with_scalar(Vector v, Fraction f);
Vector fvector_normalization(Vector v);
Fraction fvector_norm_noroot(Vector a);
string fvector_norm_print(Fraction a);
Fraction fvector_scalar_product(Vector a, Vector b);
Vector fvector_cross_product(Vector a, Vector b);
float fvector_float_norm(Vector a);
float fvector_angle(Vector a, Vector b);

#endif