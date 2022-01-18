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

FVector init(FVector m);
FVector fraction_vector_copy(FVector a);


#endif