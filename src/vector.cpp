#include <iostream>
#include <cstdlib>
#include <ctime>
#include "all-headers.h"
using namespace std;

float vector_euclid_scalar_multip(Vector a, Vector b){
    int res = 0;
    if(a->n == b->n){
        for(int i = 0; i < a->n; i++){
            res += a->array[i] * b->array[i];
        }
        return res;
    } else {
        cout << endl << "The vectors are not from the same vectorial space" << endl;
        return;
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

Vector vector_vectorial_multip(Vector a, Vector b){

}
