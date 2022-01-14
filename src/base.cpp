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

/*Vector matrix_column_to_vector(Matrix m, int c){
    Vector res = new Tvettore(m->nr);
    for(int i = 0; i < m->nr; i++){
        res->array[i] = m->mat[i][c];
    }
    return res;
}*/

void matrix_column_to_vector(Vector v, Matrix m, int c){
    for(int i = 0; i < m->nr; i++){
        v->array[i] = m->mat[i][c];
    }
}

void matrix_init_column(Matrix m, Vector v, int c){
    for(int i = 0; i < m->nr; i++){
        m->mat[i][c] = v->array[i];
    }
}

Matrix gram_schmidt(Matrix m){
    Matrix a1 = new Tmatrix(m->nr, m->nc); 
    Vector v = new Tvettore(m->nr);
    Vector tmp = new Tvettore(v->n);
    Vector res = new Tvettore(v->n);
    Vector pr = new Tvettore(v->n);

    for(int i = 0; i < m->nc; i++){
        if(i == 0){
            matrix_column_to_vector(v, m, 0);
            matrix_init_column(a1, v, 0);
        } else {
            matrix_column_to_vector(v, m, i);
            vector_copy_vector(res, v);
            for(int j = 0; j < i; j++){
                matrix_column_to_vector(tmp, m, j);
                pr = vector_pr(v, tmp);
                vector_subtraction(res, pr);
            }
            matrix_init_column(a1, res, i);
        }
    }

    return a1;
}

Matrix matrix_orthonormal_base(Matrix m){ // only works if the vectors are independent
    Matrix a = new Tmatrix(m->nr, m->nc);
    Vector v = new Tvettore(m->nr);
    a = gram_schmidt(m); // needs to be normalized

    for(int i = 0; i < a->nc; i++){
        matrix_column_to_vector(v, a, i);
        v->multiply(1 / vector_norm(v));

        matrix_init_column(a, v, i);
    }

    return a;
}