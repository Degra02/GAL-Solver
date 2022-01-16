#include <iostream>
#include "matrix_list.h"
#include "vector_list.h"
using namespace std;

#ifndef __DATABASE_H__
#define __DATABASE_H__

typedef struct Tlists{
    MNodeptr Mlist;
    VNodeptr Vlist;

    Tlists(){
        Mlist = NULL;
        Vlist = NULL;
    }

    ~Tlists(){}

}Tlists;

typedef Tlists *Lists;

#endif
