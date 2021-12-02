#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
using namespace std;

#ifndef __MATRICI_H__
#define __MATRICI_H__

typedef struct Tmatrix{ // Struct Tmatrix 
    float **mat;
    int nr;
    int nc;

    Tmatrix(){ // default constructor
        nr = nc = 0;
    }

    Tmatrix(int _nr, int _nc){ // Matrix init
        nr = _nr;
        nc = _nc;
        mat = new float*[nr];
        for(int i = 0; i < nr; i++){
            mat[i] = new float[nc];
        }
    }

    Tmatrix(int _nr, int _nc, int min, int max){ // Random number init constructor
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

    void copy_matrix(Tmatrix *a){ // Initializes the current matrix by copying a new one
        nr = a->nr;
        nc = a->nc;
        mat = new float*[nr];
        for(int i = 0; i < nr; i++){
            mat[i] = new float[nc];
            for(int j = 0; j < nc; j++){
                mat[i][j] = a->mat[i][j];
            }
        }
    }

    ~Tmatrix(){ // Destroy f.
        for(int i = 0; i < nr; i++)
            delete[] mat[i];

        delete[] mat;
    }

    void stampa() const { // print f.
        for(int i = 0; i < nr; i++){
            for(int j = 0; j < nc; j++){
                printf(" %5.1f ", mat[i][j]);
            }
            cout << endl << endl;
        }
    }

    void sum(Tmatrix *b){ //Sums a new matrix to the current one
        for(int i = 0; i < nr; i++){
            for(int j = 0; j < nc; j++){
                mat[i][j] = b->mat[i][j] + b->mat[i][j];
            }
        }
    }

} Tmatrix;

typedef Tmatrix* Matrix; 

Matrix matrix_transpose(Matrix m);
void matrix_sum(Tmatrix *sum, Tmatrix *a, Tmatrix *b);
Matrix matrix_multiplication(Matrix a, Matrix b);
void S(Matrix m, int d, int s); // Change rows operation
void D(Matrix m, int a, float lambda);
void E(Matrix m, int d, int s, float lambda); // Add a row to another, multiplied by lambda

#endif
