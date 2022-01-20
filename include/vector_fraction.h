#include "all-headers.h"
#include <iostream>
#ifndef __VECTOR_FRACTION_H__
#define __VECTOR_FRACTION_H__
using namespace std;

typedef struct Tfvector { 
    Fraction *array; int n;
    string name;

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
void print_fvector(FVector v);

FVector fraction_vector_copy(FVector a);
bool fvector_same_dimension(FVector a, FVector b);
FVector fvector_sum(FVector a, FVector b);
FVector fvector_difference(FVector a, FVector b);
Fraction fvector_norm_noroot(FVector a);
string fvector_norm_print(Fraction a);
Fraction fvector_scalar_product(FVector a, FVector b);
float fvector_float_norm(FVector a);
float fvector_angle(FVector a, FVector b);

#endif