#include <iostream>
#include <cstdlib>
#include <ctime>
#include "all-headers.h"
using namespace std;

#ifndef __VECTOR_H__
#define __VECTOR_H__

typedef struct Tvettore{ // Struct Tvettore
    float *array;
    int n;

    Tvettore(){ // Costruttore di default
        n = 0;
    }

    Tvettore(int _n){ // Costruttore per dimensione vettore
        n = _n;
        array = new float[n];
    }

    Tvettore(float *values, int dim){ // Inizializzazione vettore con "dim" values inserite da utente
        n = dim;
        array = new float[n];
        for(int i = 0; i < n; i++){
            array[i] = values[i];
        }
    }

    Tvettore(int _n, int min, int max){ // Inizializzazione vettore con _n valori casuali
        n = _n;
        array = new float[n];
        for(int i = 0; i < n; i++){
            array[i] = (rand() % (max*10 - min*10 + 1) + min*10)/10.0;
        }
    }

    ~Tvettore(){ // Distruttore array
        delete[] array;
    }

    void stampa() const{ // Stampa array
        for(int i = 0; i < n; i++){
            printf(" %2.1f ", array[i]);
        }
    }

    void multiply(float lambda){
        for(int i = 0; i < n; i++){
            array[i] *= lambda;
        }
    }

    void init(int _n) {
        n = _n;
        array = new float[n];
        float coe;
        for (int i=0; i<n; i++) {
            printf("insert number in [%d]: ", i+1); scanf("%f", &coe);
            array[i] = coe;
        }
    }
}Tvettore;

typedef Tvettore *Vector;
float vector_euclid_scalar_multip(Vector a, Vector b);
float vector_norm(Vector a);
float vector_angle(Vector a, Vector b);
Vector vector_vectorial_multip(Vector a, Vector b);
Vector vector_pr(Vector i, Vector pr);
bool vector_same_dimension(Vector a, Vector b);
Vector vector_copy_vector(Vector dest, Vector src);
Vector matrix_row_to_vector(Matrix m, int row);

#endif
