#include <iostream>
#include "all-headers.h"

#ifndef __EQ_SYSTEMS_H__
#define __EQ_SYSTEMS_H__
using namespace std;

typedef struct Tlisys {
    Matrix A;
    Vector b; 

    Tlisys() {
        A = new Tmatrix();
        b = new Tvettore();
    }

    Tlisys(Matrix _A, Vector _b) {
        A = _A;
        b = _b;
    }

    Tlisys(int n_var, int n_eq) {
        A->init(n_var, n_eq);
        b->init(n_eq);
    }

    void stampa() {
        for(int i = 0; i < A->nr; i++){
            for(int j = 0; j < A->nc; j++){
                if(A->mat[i][j] == 0){
                    printf(" %6d", 0);
                } else {
                    if(floor(A->mat[i][j]) == A->mat[i][j]){
                        printf(" %6.0f ", A->mat[i][j]);
                    } else {
                        printf(" %5.1f ", A->mat[i][j]);
                    }
                }
            }
            if(b->array[i] == 0){
                printf(" | %6d", 0);
            } else {
                if(floor(b->array[i]) == 0){
                    printf(" | %6.0f", b->array[i]);
                } else {
                    printf(" | %5.1f", b->array[i]);
                }
            }
            cout << endl << endl;
        }
    }

    ~Tlisys(){
        A->~Tmatrix();
        b->~Tvettore();
    }

} Tlisys; 

typedef Tlisys* Linear_System;
Matrix to_matrix(Linear_System ls);
Matrix ls_rref(Linear_System ls);
void ls_stairs_gauss_jordan(Matrix m);
void ls_rref_calculator(Matrix m);
Matrix ls_rref_full(Linear_System ls);

#endif
