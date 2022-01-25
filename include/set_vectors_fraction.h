#include "all-headers.h"
#ifndef __SET_VECTORS_FRACTION_H__
#define __SET_VECTORS_FRACTION_H__

typedef struct TsetFVectors {
    FVector* v;
    string name;
    int dim;
    int n_th;

    TsetFVectors(string _n);
    TsetFVectors(int x, int y, string _n);
    ~TsetFVectors();
    void print() const;

} TsetFVectors;

typedef TsetFVectors* setFVectorsPtr;

setFVectorsPtr init_set_fvectors(string name);
setFVectorsPtr init_set_fvectors_base(string name);
setFVectorsPtr insert_values_set_fvectors(int _dim, int _n_th, string name);
void print_set_fvectors(setFVectorsPtr sv);

FMatrix set_vectors_to_fmatrix(setFVectorsPtr sv);

bool set_fvectors_is_linearly_independent(setFVectorsPtr sv);
bool set_fvectors_is_generators(setFVectorsPtr sv);
bool set_fvectors_is_base(setFVectorsPtr sv);

setFVectorsPtr Gram_Schmidt(setFVectorsPtr sv);
setFVectorsPtr orthogonal_complement(setFVectorsPtr sv);

#endif
