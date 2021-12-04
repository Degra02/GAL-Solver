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

void ls_stairs_form(Matrix m){
    int c = 0;
    float lambda = 0;

    while(c < m->nc-1){
        for(int i = 0; i < m->nr; i++){
            if(m->mat[i][c]){
                for(int k = i+1; k < m->nr; k++){
                    if(m->mat[k][c]){
                        lambda = -(m->mat[k][c] / m->mat[i][c]);
                        E(m, k, i, lambda);
                    } else {
                        continue;
                    }
                }
                c++;
            } else {
                if(i < m->nr-1){
                    for(int k = i+1; k < m->nr; k++){
                        if(m->mat[k][c]){
                            S(m, k, i);
                        }
                    }
                }
                c++;
            }
        }
    }
}

Matrix ls_rref(Linear_System ls){
    Matrix sol = to_matrix(ls);
    ls_stairs_form(sol);

    return sol;
}