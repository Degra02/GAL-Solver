#include <iostream>
#include <ctime>
#include <bits/stdc++.h>
#include "all-headers.h"
using namespace std;

FMatrix to_fmatrix(FEqsys e){
    FMatrix m = new Tfmatrix(e->A->nr, e->A->nc + 1);
    for(int i = 0; i < m->nr; i++){
        for(int j = 0; j < m->nc; j++){
            if(j == (m->nc - 1)){
                m->mat[i][j] = e->b->array[i];
            } else {
                m->mat[i][j] = e->A->mat[i][j];
            }
        }
    }
    return m;
}

FEqsys to_feqsys_from_matrix(FMatrix m){ // creates an eq system from a matrix
    FEqsys res = new Tfeqsys(new Tfmatrix(m->nr, m->nc - 1), new Tfvector(m->nr));
    for(int i = 0; i < m->nr; i++){
        for(int j = 0; j < m->nc; j++){
            if(j == m->nc - 1){
                res->b->array[i] = m->mat[i][j];
            } else {
                res->A->mat[i][j] = m->mat[i][j];
            }
        }
    }
    return res;
}

FEqsys feq_sys_stairs_form(FEqsys e){
    FMatrix tmp = to_fmatrix(e);
    tmp = fraction_matrix_gauss_jordan(tmp);
    return to_feqsys_from_matrix(tmp);
}