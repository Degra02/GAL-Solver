#include <iostream>
#include <cstdlib>
#include <ctime>
#include "base.h"
#include "all-headers.h"
using namespace std;

bool matrix_is_square(Matrix m){ // returns true if it's a square matrix
    return (m->nc == m->nr);
}

bool matrix_is_base(Matrix m){ // returns true if the vectors are independent
    return ((matrix_is_square(m)) && (rg(m) == m->nr));
}

Vector matrix_column_to_vector(Matrix m, int c){
    Vector res = new Tvettore(m->nc);
    for(int i = 0; i < m->nr; i++){
        res->array[i] = m->mat[i][c];
    }
    return res;
}

void matrix_init_column(Matrix m, Vector v, int c){
    for(int i = 0; i < m->nr; i++){
        m->mat[i][c] = v->array[i];
    }
}

Matrix gram_schmidt(Matrix m, Vector v){
    Matrix a1 = new Tmatrix(m->nr, m->nc); 
    Vector tmp = new Tvettore(v->n);
    Vector res = new Tvettore(v->n);

    for(int i = 0; i < m->nc; i++){
        if(i == 0){
            v = vector_copy_vector(v, matrix_column_to_vector(m, 0));
            matrix_init_column(a1, v, 0);
        } else {
            v = matrix_column_to_vector(m, i);
            for(int j = 0; j < i; j++){
                tmp = vector_pr(v, matrix_column_to_vector(a1, j));
                res = vector_subtraction(v, tmp);
            }
            matrix_init_column(a1, res, i);
        }
    }

    return a1;
}

Matrix matrix_orthonormal_base(Matrix m){ // only works if the vectors are independent
    Vector v = new Tvettore(m->nr);
    Matrix a = new Tmatrix(m->nr, m->nc);
    a = gram_schmidt(m, v); // needs to be normalized

    for(int i = 0; i < a->nc; i++){
        v = matrix_column_to_vector(a, i);
        v->multiply( (1 / pow(vector_norm(v), 2)));

        matrix_init_column(a, v, i);
    }

    return a;
}