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

    /*Tlisys(int num_variables, int num_eq) {
        A = new Tmatrix(num_eq, num_variables);
        A->init(); // da modificare 
        b = new Tvettore(num_eq);
        b->init(); // da modificare 
    }*/

    void stampa() {
        for(int i = 0; i < A->nr; i++){
            for(int j = 0; j < A->nc; j++){
                printf(" %5.1f ", A->mat[i][j]);
            }
            printf(" |  %5.1f ", b->array[i]);
            cout << endl << endl;
        }
    }
} Tlisys; 

typedef Tlisys* Linear_System;
Matrix to_matrix(Linear_System ls);
Matrix ls_rref(Linear_System ls);
void ls_stairs_gauss_jordan(Matrix m);
void ls_rref_calculator(Matrix m);
Matrix ls_rref_full(Linear_System ls);

#endif
