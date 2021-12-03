#include <iostream>
#include "matrici.h"
#include "vettori.h"
#ifndef __EQ_SISTEMI_H__
#define __EQ_SISTEMI_H__
using namespace std;

typedef struct System {
    Matrix A;
    Vector b; 

    System() {
        A = new Tmatrix();
        b = new Tvettore();
    }

    System(int num_variables, int num_eq) {
        A = new Tmatrix(num_eq, num_variables);
        A->init(); // da modificare 
        b = new Tvettore(num_eq-1);
        b->init(); // da modificare 
    }

    void stampa() {
        for(int i = 0; i < A->nr; i++){
            for(int j = 0; j < A->nc; j++){
                printf(" %5.1f ", A->mat[i][j]);
            }
            printf(" |  %5.1f ", b->array[i]);
            cout << endl << endl;
        }
    }
} System; 

#endif
