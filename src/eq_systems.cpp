#include <iostream>
#include <cstdlib>
#include <ctime>
#include "all-headers.h"
using namespace std;

Matrix to_matrix(Linear_System ls){
    Matrix m = new Tmatrix(ls->A->nr, ls->A->nc + 1);
    for(int i = 0; i < m->nr; i++){
        for(int j = 0; j < m->nc; j++){
            if(j != m->nc - 1){
                m->mat[i][j] = ls->A->mat[i][j];
            } else {
                m->mat[i][j] = ls->b->array[i];
            }
        }
    }

    return m;
}