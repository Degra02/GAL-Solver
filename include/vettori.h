#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

#ifndef __VETTORI_H__
#define __VETTORI_H__

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

    Tvettore(float values[], int dim){ // Inizializzazione vettore con "dim" values inserite da utente
        n = dim;
        array = new float[n];
        for(int i = 0; i < n; i++){
            array[i] = values[i];
        }
    }

    Tvettore(int _n, int min, int max){ // Inizializzazione vettore con _n valori casuali
        n = _n;
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

}Tvettore;

typedef Tvettore *Vector; // rendere più semplice la lettura

#endif
