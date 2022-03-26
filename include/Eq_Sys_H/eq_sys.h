#include <iostream>
#include "all-headers.h"
#include "Other_H/set.h"
using namespace std;

#ifndef __EQ_SYS_H__
#define __EQ_SYS_H__

typedef struct Tfeqsys{
    Matrix A;
    Vector b;
    string name;

    Tfeqsys() {
        A = NULL;
        b = NULL;
    }

    Tfeqsys(Matrix _A, Vector _b) {
        A = _A;
        b = _b;
    }

    Tfeqsys(Matrix _A, Vector _b, string _name) {
        A = _A;
        b = _b;
        name = _name;
    }

} Tfeqsys;

typedef enum Trc { INF_RESULTS, NO_RESULT, ONE_RESULT } Trc;

typedef Tfeqsys *FEqsys;

FEqsys init_feqsys(string name);
void print_feqsys(FEqsys e);
Matrix to_fmatrix(FEqsys e);
FEqsys feq_sys_rref(FEqsys e);
FEqsys to_feqsys_from_matrix(Matrix m);
Trc Rouche_Capelli(FEqsys e);
Set feq_sys_sol(FEqsys e);
Set feq_sys_inf_sol(FEqsys e);
Set feq_sys_one_sol(FEqsys e);
Set set_base_inf_sol(FEqsys e, FreeColumnsPtr fc, PivotRowsColumnsPtr pcr);

#endif
