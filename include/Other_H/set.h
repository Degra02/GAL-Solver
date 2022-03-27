#include "Vector_H/vector.h"
#ifndef __SET_H__
#define __SET_H__

typedef struct TsetFVectors
{
    Vector *v;
    string name;
    int dim;
    int n_th;

    TsetFVectors(string _n);
    TsetFVectors(int _dim, int _n_th);
    TsetFVectors(int x, int y, string _n);
    ~TsetFVectors();
    void print() const;

} TsetFVectors;

typedef TsetFVectors *Set;

Set init_set_fvectors(string name);
Set init_set_fvectors_base(string name);
Set init_set_fvectors_base_function(string name, int _n_th);
Set init_base(int _dim, int _n_th, string name);
Set insert_values_set_fvectors(int _dim, int _n_th, string name);
void print_set_fvectors(Set sv);
Set id(int dim);
int parse_canonical_base(string name);
bool set_fvectors_is_linearly_independent(Set sv);
bool set_fvectors_is_generators(Set sv);
bool set_fvectors_is_base(Set sv);
Set Gram_Schmidt(Set sv);
Set orthogonal_complement(Set sv);
Set completion_of_base(Set sv);

#endif
