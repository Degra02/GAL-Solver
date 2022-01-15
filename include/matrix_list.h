#include <iostream>
#include "all-headers.h"
using namespace std;

#ifndef __MATRIX_LIST__
#define __MATRIX_LIST__

typedef struct Tnode{
    Matrix m;
    Tnode *next;

    Tnode(){
        m = NULL;
        next = NULL;
    }

    Tnode(Matrix _m, Tnode *_next){
        m = _m;
        next = _next;
    }

    ~Tnode(){}

}Tnode;

typedef Tnode *Nodeptr;

Nodeptr insertFirst(Nodeptr n, Matrix m);
Nodeptr remove_search(Nodeptr n);
Matrix get(Nodeptr n);
Matrix get_search(Nodeptr n);
bool isPresent(Nodeptr n, string name);
Nodeptr insert(Nodeptr n);


#endif
