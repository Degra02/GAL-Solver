#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

#ifndef __MATRICI_H__
#define __MATRICI_H__

typedef struct Tmatrice{ // Struct Tmatrice 
    float **mat;
    int nr;
    int nc;

    Tmatrice(){ // Costruttore di default
        nr = nc = 0;
    }

    Tmatrice(int _nr, int _nc){ // Inizializza matrice
        nr = _nr;
        nc = _nc;
        mat = new float*[nr];
        for(int i = 0; i < nr; i++){
            mat[i] = new float[nc];
        }
    }

    Tmatrice(int _nr, int _nc, int min, int max){ // Costruttore matrice con numeri casuali
        nr = _nr;
        nc = _nc;
        mat = new float*[nr];
        for(int i = 0; i < nr; i++){
            *(mat + i) = new float[nc];
            for(int j = 0; j < nc; j++){
                *( *(mat + i) + j) = (rand() % (max*10 - min*10 + 1) + min*10)/10.0;
            }
        }
    }

    ~Tmatrice(){ // Distruttore matrice
        for(int i = 0; i < nr; i++)
            delete[] mat[i];

        delete[] mat;
    }

    void stampa() const { // Stampa matrice
        for(int i = 0; i < nr; i++){
            for(int j = 0; j < nc; j++){
                printf(" %2.1f ", mat[i][j]);
            }
            cout << endl;
        }
    }

    void sum(Tmatrice *b){ //Sums a new matrix to the current one
        for(int i = 0; i < nr; i++){
            for(int j = 0; j < nc; j++){
                mat[i][j] = b->mat[i][j] + b->mat[i][j];
            }
        }
    }

} Tmatrice;

typedef Tmatrice* Matriceptr;

void matrix_sum(Tmatrice *sum, Tmatrice *a, Tmatrice *b);
Matriceptr matrix_multiplication(Matriceptr a, Matriceptr b);

#endif
