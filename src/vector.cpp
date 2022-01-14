#include <iostream>
#include <cstdlib>
#include <ctime>
#include "all-headers.h"
using namespace std;

Vector vector_sum(Vector a, Vector b){
    Vector res = new Tvettore(a->n);
    for(int i = 0; i < a->n; i++){
        res->array[i] = a->array[i] + b->array[i];
    }

    return res;
}

void vector_subtraction(Vector a, Vector b){
    for(int i = 0; i < a->n; i++){
        a->array[i] = a->array[i] - b->array[i];
    }
}

float vector_euclid_scalar_multip(Vector a, Vector b){
    int res = 0;
    if(a->n == b->n){
        for(int i = 0; i < a->n; i++){
            res += a->array[i] * b->array[i];
        }
        return res;
    } else {
        cout << endl << "The vectors are not from the same vectorial space" << endl;
        return 0;
    }
}

float vector_norm(Vector a){
    int norm2 = 0;
    for(int i = 0; i < a->n; i++){
        norm2 += pow(a->array[i], 2);
    }

    return sqrt(norm2);
}

float vector_angle(Vector a, Vector b){
    float angle = vector_euclid_scalar_multip(a, b) / (vector_norm(a) * vector_norm(b));
    return acos(angle);
}

Vector vector_vectorial_multip(Vector a, Vector b){ // possible only in R3 (or R7)
    if(a->n == b->n && a->n == 3){
        Vector c = new Tvettore(a->n);
        c->array[0] = a->array[1]*b->array[2] - a->array[3]*b->array[2];
        c->array[1] = a->array[2]*b->array[0] - a->array[0]*b->array[2];
        c->array[2] = a->array[0]*b->array[1] - a->array[1]*b->array[0];
        return c;
    } else {
        cout << endl << "The vectorial product is only possible in the third (or seventh) dimension" << endl;
        return NULL;
    }
}

Vector vector_pr(Vector i, Vector pr){
    Vector res = new Tvettore(i->n);
    vector_copy_vector(res, pr);
    float lambda;
    lambda = (vector_euclid_scalar_multip(i, pr)/(pow(vector_norm(pr), 2)));
    res->multiply(lambda);
    
    return res;
}

bool vector_same_dimension(Vector a, Vector b){
    return (a->n == b->n);
}

void vector_copy_vector(Vector dest, Vector src){
    if(vector_same_dimension(dest, src)){
        for(int i = 0; i < src->n; i++){
            dest->array[i] = src->array[i];
        }
    }
}

Vector matrix_row_to_vector(Matrix m, int row){
    Vector res = new Tvettore(m->nc);
    for(int j = 0; j < m->nc; j++){
        res[j] = m->mat[row][j];
    }

    return res;
}
