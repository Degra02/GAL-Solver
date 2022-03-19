#include "all-headers.h"
#include "Vector_H/vector.h"
#include <iostream>
#ifndef __MATRIX_H__
#define __MATRIX_H__
using namespace std;

typedef struct TfreeColumns{
    int* free_columns;
    int dim;

    TfreeColumns(){
        dim = 0;
    }

    TfreeColumns(int x){
        dim = x;
        free_columns = new int[dim];
    }

    ~TfreeColumns(){
        delete[] free_columns;
    }

}TfreeColumns;

typedef TfreeColumns* FreeColumnsPtr;

typedef struct TpivotRowsColmuns{
    int* pivot_rows;
    int* pivot_columns;
    int dim;

    TpivotRowsColmuns(){
        dim = 0;
    }

    TpivotRowsColmuns(int x){
        dim = x;
        pivot_rows = new int[dim];
        pivot_columns = new int[dim];
    }

    ~TpivotRowsColmuns(){
        delete[] pivot_rows;
        delete[] pivot_columns;
    }

}TpivotRowsColmuns;

typedef TpivotRowsColmuns* PivotRowsColumnsPtr;

/* TYPE FRACTION MATRIX */
typedef struct Tfmatrix{
    Fraction **mat;
    int nr; int nc;
    string name;

    Tfmatrix();
    Tfmatrix(int _nr, int _nc);
    Tfmatrix(string _name, int _nr, int _nc);
    Tfmatrix(int _nr, int _nc, int min, int max);
    ~Tfmatrix();
}Tfmatrix;

typedef Tfmatrix* FMatrix; 

FMatrix init_fmatrix(string name);
FMatrix init_fmatrix_known_dim(string name, int r, int c);
FMatrix init_predefinition_fmatrix(string name, int r, int c);
FMatrix insert_values_fmatrix(int r, int c, string name);
void print_fmatrix(FMatrix m);
void print_fmatrix_system(FMatrix m);
void print_fmatrix_float(FMatrix m);
void print_fmatrix_float_system(FMatrix m);
int fraction_find_max_figures_column(FMatrix m, int colummn, char type);
int float_find_max_figures_column(float** f, int dim, int column);
FMatrix fraction_matrix_transpose(FMatrix m);
FMatrix fraction_matrix_sum(FMatrix a, FMatrix b);
FMatrix fraction_matrix_difference(FMatrix a, FMatrix b);
FMatrix fraction_matrix_multiplication(FMatrix a, FMatrix b);
FMatrix fraction_matrix_scalar_multiplication(FMatrix a, float lambda);
FMatrix fraction_matrix_reverse(FMatrix m);
void fraction_S(FMatrix m, int a, int b);
void fraction_D(FMatrix m, int a, Fraction lambda);
void fraction_E(FMatrix m, int d, int s, Fraction lambda);
FMatrix fraction_matrix_copy(FMatrix m);
FMatrix fraction_matrix_gauss_jordan(FMatrix m);
FMatrix fraction_matrix_rref(FMatrix m);
int fraction_matrix_rank(FMatrix m);
bool fraction_matrix_is_base(FMatrix m);
bool matrix_is_square(FMatrix m);
FVector fraction_matrix_fvector_product(FMatrix m, FVector v);
PivotRowsColumnsPtr pivot_rows_columns(FMatrix m);
FreeColumnsPtr free_columns(FMatrix m);

#endif
