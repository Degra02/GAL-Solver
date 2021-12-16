#include "all-headers.h"
#include <iostream>
#ifndef __VECTOR_FRACTION_H__
#define __VECTOR_FRACTION_H__
using namespace std;

typedef struct Tfvector { 
    Fraction *array; int n;

    Tfvector();
    Tfvector(int _n);
    Tfvector(float *values, int dim);
    Tfvector(Fraction* values, int dim);
    Tfvector(int _n, int min, int max);
    ~Tfvector();
    void print() const;
    void init();
    void multiply(float lambda);
} Tfvector;

typedef Tfvector* FVector;

FVector init(FVector m);

#endif