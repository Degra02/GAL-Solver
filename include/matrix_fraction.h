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

FMatrix init_fmatrix(string name);
void print_fmatrix(FMatrix m);
void print_fmatrix_float(FMatrix m);

int fraction_find_max_figures_column(FMatrix m, int colummn, char type);
int float_find_max_figures_column(float** f, int dim, int column);

FMatrix fraction_matrix_transpose(FMatrix m);
FMatrix fraction_matrix_sum(FMatrix a, FMatrix b);
FMatrix fraction_matrix_difference(FMatrix a, FMatrix b);
FMatrix fraction_matrix_multiplication(FMatrix a, FMatrix b);
FMatrix fraction_matrix_scalar_multiplication(FMatrix a, float lambda);

void fraction_S(FMatrix m, int a, int b);
void fraction_D(FMatrix m, int a, Fraction lambda);
void fraction_E(FMatrix m, int d, int s, Fraction lambda);

FMatrix fraction_matrix_copy(FMatrix m);

FMatrix fraction_matrix_gauss_jordan(FMatrix m);
FMatrix fraction_matrix_rref(FMatrix m);
int fraction_matrix_rank(FMatrix m);
bool fraction_matrix_is_base(FMatrix m);
bool matrix_is_square(FMatrix m);

#endif
