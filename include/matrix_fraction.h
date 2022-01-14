#include "all-headers.h"
#include <iostream>
#ifndef __MATRIX_FRACTION_H__
#define __MATRIX_FRACTION_H__
using namespace std;

/* TYPE FRACTION MATRIX */
typedef struct Tfmatrix {
    Fraction **mat;
    int nr; int nc;
    string name;

    Tfmatrix();
    Tfmatrix(int _nr, int _nc);
    Tfmatrix(string _name, int _nr, int _nc);
    Tfmatrix(int _nr, int _nc, int min, int max);
    void print() const;
    void init();
    ~Tfmatrix();
} Tfmatrix;

typedef Tfmatrix* FMatrix; 

FMatrix init_fmatrix();
Fraction str_to_fraction(string value);
FMatrix fraction_matrix_transpose(FMatrix m);
FMatrix fraction_matrix_sum(FMatrix a, FMatrix b);
FMatrix fraction_matrix_multiplication(FMatrix a, FMatrix b);
FMatrix fraction_matrix_scalar_multiplication(FMatrix a, float lambda);

void fraction_S(FMatrix m, int a, int b);
void fraction_D(FMatrix m, int a, Fraction lambda);
void fraction_E(FMatrix m, int d, int s, Fraction lambda);

bool fraction_is_stairs_form(FMatrix m);
void fraction_matrix_gauss_jordan(FMatrix m);

#endif
