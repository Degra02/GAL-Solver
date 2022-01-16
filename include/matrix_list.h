#include <iostream>
#include "all-headers.h"
using namespace std;

#ifndef __MATRIX_LIST__
#define __MATRIX_LIST__

typedef struct TMnode{
    Matrix m;
    TMnode *next;

    TMnode(){
        m = NULL;
        next = NULL;
    }

    TMnode(Matrix _m, TMnode *_next){
        m = _m;
        next = _next;
    }

    ~TMnode(){}

}TMnode;

typedef TMnode *MNodeptr;

MNodeptr insertFirst(MNodeptr n, Matrix m);
MNodeptr remove_search(MNodeptr n);
Matrix get(MNodeptr n);
Matrix get_search(MNodeptr n, string name);
bool isPresent(MNodeptr n, string name);
MNodeptr insert(MNodeptr n, string name);


#endif
