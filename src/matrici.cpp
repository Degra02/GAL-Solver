#include <iostream>
#include <cstdlib>
#include <ctime>
#include "matrici.h"
#include "determinanti.h"
#include "vettori.h"
using namespace std;

Matrix matrix_multiplication(Matrix a, Matrix b){
    Matrix multi;
    if(a->nc == b->nr){
        multi = new Tmatrix(a->nr, b->nc);
        for(int i = 0; i < multi->nr; i++){
            for(int j = 0; j < multi->nc; j++){
                multi->mat[i][j] = 0;
                for(int k = 0; k < multi->nc; k++){
                    multi->mat[i][j] += (a->mat[i][k])*(b->mat[k][j]);
                }
            }
        }
    return multi;

    } else {
        cout << "Impossible to multiplicate the given functions";
        exit(1);
    }
}

void S(Matrix m, int a, int b){
    Vector v = new Tvettore(m->mat[a-1], m->nc);
    m->mat[a-1] = m->mat[b-1];
    m->mat[b-1] = v->array;
}

void D(Matrix m, int a, float lambda){
    for(int j = 0; j < m->nc; j++){
        m->mat[a-1][j] = m->mat[a-1][j]*lambda;
    }
}

void E(Matrix m, int d, int s, float lambda){ // d = destination, s = source;
    Vector v = new Tvettore(m->mat[s-1], m->nc);
    v->multiply(lambda);
    for(int j = 0; j < m->nc; j++){
        m->mat[d-1][j] = m->mat[d-1][j] + v->array[j];
    }
    
    v->~Tvettore();
}