#include <iostream>
#include "all-headers.h"
using namespace std;

#ifndef __EQ_SYS_FRACTION_H__
#define __EQ_SYS_FRACTION_H__

typedef struct Tfeqsys{
    FMatrix A;
    FVector b;
    string name;

    Tfeqsys(){
        A = NULL;
        b = NULL;
    }

    Tfeqsys(FMatrix _A, FVector _b){
        A = _A;
        b = _b;
    }

    Tfeqsys(FMatrix _A, FVector _b, string _name){
        A = _A;
        b = _b;
        name = _name;
    }

}Tfeqsys;

typedef Tfeqsys *FEqsys;

FEqsys init_feqsys(string name);
FMatrix to_fmatrix(FEqsys e);
FEqsys feq_sys_stairs_form(FEqsys e);
FEqsys to_feqsys_from_matrix(FMatrix m);


#endif
