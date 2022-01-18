#include "all-headers.h"
#ifndef __BASE_FRACTION_H__
#define __BASE_FRACTION_H__

typedef struct Tfbase {
    int dim; int n_th;
    string name;
    FVector* v;

    Tfbase(int x, int th, string _n);
    ~Tfbase();
    void print() const;
} Tfbase;
    
typedef Tfbase* FBase;

FBase init_fbase(string name);
void print_fbase(FBase b);

#endif
