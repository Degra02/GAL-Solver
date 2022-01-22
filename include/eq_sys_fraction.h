#include <iostream>
#include "all-headers.h"
#include "set_vectors_fraction.h"
using namespace std;

#ifndef __EQ_SYS_FRACTION_H__
#define __EQ_SYS_FRACTION_H__

typedef struct Tfeqsys{
    FMatrix A;
    FVector b;
    string name;

    Tfeqsys() {
        A = NULL;
        b = NULL;
    }

    Tfeqsys(FMatrix _A, FVector _b) {
        A = _A;
        b = _b;
    }

    Tfeqsys(FMatrix _A, FVector _b, string _name) {
        A = _A;
        b = _b;
        name = _name;
    }

} Tfeqsys;

typedef enum Trc { INF_RESULTS, NO_RESULT, ONE_RESULT } Trc;

typedef Tfeqsys *FEqsys;

FEqsys init_feqsys(string name);
void print_feqsys(FEqsys e);

FMatrix to_fmatrix(FEqsys e);

FEqsys feq_sys_rref(FEqsys e);
FEqsys to_feqsys_from_matrix(FMatrix m);

Trc Rouche_Capelli(FEqsys e);
setFVectorsPtr feq_sys_sol(FEqsys e);

#endif
