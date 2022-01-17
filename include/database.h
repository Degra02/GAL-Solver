#include <iostream>
#include "matrix_list.h"
#include "vector_list.h"
#include "eq_sys_fraction.h"
using namespace std;

#ifndef __DATABASE_H__
#define __DATABASE_H__

typedef struct Tlists{
    MNodeptr Mlist;
    VNodeptr Vlist;
    FEqsys Eqlist;

    Tlists(){
        Mlist = NULL;
        Vlist = NULL;
        Eqlist = NULL;
    }

    ~Tlists(){}

}Tlists;

typedef Tlists *Lists;

#endif
