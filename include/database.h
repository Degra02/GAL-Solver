#include <iostream>
#include "matrix_list.h"
using namespace std;

#ifndef __DATABASE_H__
#define __DATABASE_H__

typedef struct Tlists{
    MNodeptr Mlist;

    Tlists(){
        Mlist = NULL;
    }

    ~Tlists(){}

}Tlists;

typedef Tlists *Lists;

#endif
