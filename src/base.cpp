#include <iostream>
#include <cstdlib>
#include <ctime>
#include "all-headers.h"
using namespace std;

bool matrix_is_square(Matrix m){ // returns true if it's a square matrix
    return (m->nc == m->nr);
}

bool matrix_is_base(Matrix m){ // returns true if the vectors are independent
    return ((matrix_is_square(m)) && (rg(m) == m->nr));
}

Vector matrix_column_to_vector(Matrix m, int c){
    Vector res;
    for(int i = 0; i < m->nr; i++){
        res->array[i] = m->mat[i][c];
    }
}

void matrix_init_column(Matrix m, Vector v, int c){
    for(int i = 0; i < m->nr; i++){
        m->mat[i][c] = v->array[i];
    }
}


Matrix gram_schmidt(Matrix m, Matrix a, Vector v, int c){
    if(c == 0){
        v = matrix_column_to_vector(m, 0);
        matrix_init_column(m, v, 0);
        return m;
    } else {
        v = matrix_column_to_vector(m, c) - ();
         // DA COMPLETARE ABBASTANZA COMPLICATO
        
    }

}

Matrix matrix_orthonormal_base(Matrix m){ // only works if the vectors are independent
    Matrix a = new Tmatrix(m->nr, m->nc);

    if(matrix_is_base(m)){
        gram_schmidt(m, a, m->nr-1);
    }

    return a;
}