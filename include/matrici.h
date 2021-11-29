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
        delete[] mat;
    }

    void stampa() const { // Stampa matrice
        for(int i = 0; i < nr; i++){
            for(int j = 0; j < nc; j++){
                printf(" %2.1f ", *( *(mat + i) + j));
            }
            cout << endl;
        }
    }

} Tmatrice;

typedef Tmatrice Matrice; // Tipo Matrice di tipo Tmatrice per rendere più chiara la scrittura


#endif
