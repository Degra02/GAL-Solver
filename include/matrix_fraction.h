#include "all-headers.h"
#include <iostream>
#ifndef __MATRIX_FRACTION_H__
#define __MATRIX_FRACTION_H__
using namespace std;

/* TYPE FRACTION MATRIX */
typedef struct Tfmatrix {
    Fraction **mat;
    int nr; int nc;
    Tfmatrix();
    Tfmatrix(int _nr, int _nc);
    Tfmatrix(int _nr, int _nc, int min, int max);
    void print() const;
    void init();
    ~Tfmatrix();
} Tfmatrix;

typedef Tfmatrix* FMatrix; 

FMatrix init(FMatrix m);
FMatrix fraction_matrix_transpose(FMatrix m);
FMatrix fraction_matrix_sum(FMatrix a, FMatrix b);

#endif
