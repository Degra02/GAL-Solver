#include "all-headers.h"
#ifndef __SET_H__
#define __SET_H__

typedef struct TsetFVectors
{
    FVector *v;
    string name;
    int dim;
    int n_th;

    TsetFVectors(string _n);
    TsetFVectors(int _dim, int _n_th);
    TsetFVectors(int x, int y, string _n);
    ~TsetFVectors();
    void print() const;

} TsetFVectors;

typedef TsetFVectors *setFVectorsPtr;

setFVectorsPtr init_set_fvectors(string name);
setFVectorsPtr init_set_fvectors_base(string name);
setFVectorsPtr init_set_fvectors_base_function(string name, int _n_th);
setFVectorsPtr init_base(int _dim, int _n_th, string name);
setFVectorsPtr insert_values_set_fvectors(int _dim, int _n_th, string name);
void print_set_fvectors(setFVectorsPtr sv);
setFVectorsPtr id(int dim);
int parse_canonical_base(string name);
FMatrix set_vectors_to_fmatrix(setFVectorsPtr sv);
bool set_fvectors_is_linearly_independent(setFVectorsPtr sv);
bool set_fvectors_is_generators(setFVectorsPtr sv);
bool set_fvectors_is_base(setFVectorsPtr sv);
setFVectorsPtr Gram_Schmidt(setFVectorsPtr sv);
setFVectorsPtr orthogonal_complement(setFVectorsPtr sv);
setFVectorsPtr completion_of_base(setFVectorsPtr sv);

#endif
