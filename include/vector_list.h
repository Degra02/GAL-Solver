#include <iostream>
#include "all-headers.h"
using namespace std;

#ifndef __VECTOR_LIST_H__
#define __VECTOR_LIST_H__

typedef struct TVnode{
    FVector v;
    TVnode *next;

    TVnode(){
        v = NULL;
        next = NULL;
    }

    TVnode(FVector _v, TVnode *_next){
        v = _v;
        next = _next;
    }

    ~TVnode(){}

}TVnode;

typedef TVnode *VNodeptr;

VNodeptr insertFirstV(VNodeptr n, FVector v);
VNodeptr remove_vsearch(VNodeptr n);
bool isPresentV(VNodeptr n, string name);
VNodeptr insertV(VNodeptr n, string name);
FVector get_vsearch(VNodeptr n, string name);

void command_print_vector(VNodeptr n);
VNodeptr command_new_vector(VNodeptr n);

#endif