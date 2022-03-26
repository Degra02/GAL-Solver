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

typedef Tfmatrix* Matrix; 

Matrix init_fmatrix(string name);
Matrix init_fmatrix_known_dim(string name, int r, int c);
Matrix init_predefinition_fmatrix(string name, int r, int c);
Matrix insert_values_fmatrix(int r, int c, string name);
void print_fmatrix(Matrix m);
void print_fmatrix_system(Matrix m);
void print_fmatrix_float(Matrix m);
void print_fmatrix_float_system(Matrix m);
int fraction_find_max_figures_column(Matrix m, int colummn, char type);
int float_find_max_figures_column(float** f, int dim, int column);
Matrix fraction_matrix_transpose(Matrix m);
Matrix fraction_matrix_sum(Matrix a, Matrix b);
Matrix fraction_matrix_difference(Matrix a, Matrix b);
Matrix fraction_matrix_multiplication(Matrix a, Matrix b);
Matrix fraction_matrix_scalar_multiplication(Matrix a, float lambda);
Matrix fraction_matrix_reverse(Matrix m);
void fraction_S(Matrix m, int a, int b);
void fraction_D(Matrix m, int a, Fraction lambda);
void fraction_E(Matrix m, int d, int s, Fraction lambda);
Matrix fraction_matrix_copy(Matrix m);
Matrix fraction_matrix_gauss_jordan(Matrix m);
Matrix fraction_matrix_rref(Matrix m);
int fraction_matrix_rank(Matrix m);
bool fraction_matrix_is_base(Matrix m);
bool matrix_is_square(Matrix m);
Vector fraction_matrix_fvector_product(Matrix m, Vector v);
PivotRowsColumnsPtr pivot_rows_columns(Matrix m);
FreeColumnsPtr free_columns(Matrix m);
Matrix check_symmetry(Matrix m);
bool is_symmetric(Matrix m);

#endif
