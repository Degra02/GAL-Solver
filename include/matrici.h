#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

#ifndef __MATRICI_H__
#define __MATRICI_H__

#define MAXN 100

typedef struct Triga{
    float valori[MAXN];
    int n;

    Triga(){
        n = 0;
    }

    Triga(int _n){
        n = _n;
    }

    Triga(int min, int max){
        for(int i = 0; i < n; i++){
            valori[i] = rand() % (max - min + 1) + min;
        }
    }

    ~Triga(){}


} Triga;

typedef struct Tcolonna{
    float valori[MAXN];
    int n;

    Tcolonna(){
        n = 0;
    }

    Tcolonna(int _n){
        n = _n;
    }

    Tcolonna(int min, int max){
        for(int i = 0; i < n; i++){
            valori[i] = rand() % (max - min + 1) + min;
        }
    }

    ~Tcolonna() {}

}Tcolonna;

typedef struct Tmatrice{
    Triga *r;
    Tcolonna *c;

    Tmatrice(){
        r = new Triga[0];
        c = new Tcolonna[0];
    }

    Tmatrice(int nr, int nc, int min, int max){
        r = new Triga[nr];
        c = new Tcolonna[nc];
        for(int i = 0; i < nr; i++){
            r[i] = Triga(nr);
            r[i] = Triga(min, max);
        }

        for(int i = 0; i < nr; i++){
            c[i] = Tcolonna(nr);
            c[i] = Tcolonna(min, max);
        }
    }

    ~Tmatrice(){
        delete[] r, c;
    }

    void stampa() const{
        for(int i = 0; i < r->n; i++){
            for(int j = 0; j < c->n; j++){
                printf("%3.1f", c->valori[j]);
            }
        }
    }

} Tmatrice;


#endif
