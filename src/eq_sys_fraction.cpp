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

FEqsys feq_sys_rref(FEqsys e){
    FMatrix tmp = to_fmatrix(e);
    tmp = fraction_matrix_rref(tmp);
    return to_feqsys_from_matrix(tmp);
}

FEqsys init_feqsys(string name){
    FEqsys eq = new Tfeqsys();
    cout << "Coefficients matrix: " << endl;
    eq->A = init_fmatrix("");
    cout << "Known terms vector: " << endl;
    eq->b = new Tfvector(eq->A->nr);
    string value;
    for(int i = 0; i < eq->A->nr; i++){
        cout << "   ";
        cin >> value;
        eq->b->array[i] = str_to_fraction(value);
        eq->b->array[i] = fraction_simplification(eq->b->array[i]);
    }
    cout << endl;

    eq->name = name;
    return eq;
}

void print_feqsys(FEqsys e) {
    FMatrix m = to_fmatrix(e);
    print_fmatrix(m);
}

Trc Rouche_Capelli(FEqsys e) {
    int rankA = fraction_matrix_rank(e->A);
    int rankAb = fraction_matrix_rank(to_fmatrix(e));
    int n = e->A->nc;

    if (rankA != rankAb) return NO_RESULT;
    if (rankA == rankAb && rankAb < n) return INF_RESULTS;
    return ONE_RESULT;
}