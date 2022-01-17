#include <iostream>
#include "all-headers.h"
using namespace std;

#ifndef __MATRIX_LIST__
#define __MATRIX_LIST__

typedef struct TMnode{
    FMatrix m;
    TMnode *next;

    TMnode(){
        m = NULL;
        next = NULL;
    }

    TMnode(FMatrix _m, TMnode *_next){
        m = _m;
        next = _next;
    }

    ~TMnode(){}

}TMnode;

typedef TMnode *MNodeptr;

MNodeptr insertFirst(MNodeptr n, FMatrix m);
MNodeptr remove_search(MNodeptr n);
FMatrix get(MNodeptr n);
FMatrix get_search(MNodeptr n, string name);
bool isPresent(MNodeptr n, string name);
MNodeptr insertM(MNodeptr n, string name);

void command_print_matrix(MNodeptr n, string userinput);
MNodeptr command_new_matrix(MNodeptr n);
MNodeptr command_matrix_product(MNodeptr n);
MNodeptr command_matrix_sum(MNodeptr n);
MNodeptr command_matrix_difference(MNodeptr n);
MNodeptr command_matrix_scalar_mult(MNodeptr n);
MNodeptr command_matrix_traspose(MNodeptr n);
MNodeptr command_matrix_stairs(MNodeptr n);

#endif
