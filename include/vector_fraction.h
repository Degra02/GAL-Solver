#include "all-headers.h"
#include <iostream>
#ifndef __VECTOR_FRACTION_H__
#define __VECTOR_FRACTION_H__
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

typedef Tfvector* FVector;

FVector init_fvector(string name);
FVector init_fvector_system(string name, int n);
void print_fvector(FVector v);

FVector fraction_vector_copy(FVector a);
bool fvector_same_dimension(FVector a, FVector b);
FVector fvector_sum(FVector a, FVector b);
FVector fvector_difference(FVector a, FVector b);
FVector fvector_product_with_scalar(FVector v, Fraction f);
FVector fvector_normalization(FVector v);
Fraction fvector_norm_noroot(FVector a);
string fvector_norm_print(Fraction a);
Fraction fvector_scalar_product(FVector a, FVector b);
FVector fvector_cross_product(FVector a, FVector b);
float fvector_float_norm(FVector a);
float fvector_angle(FVector a, FVector b);

#endif