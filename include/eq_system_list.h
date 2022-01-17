#include <iostream>
#include "all-headers.h"
using namespace std;

#ifndef __EQ_SYSTEM_LIST_H__
#define __EQ_SYSTEM_LIST_H__

typedef struct TEqnode{
    FEqsys e;
    TEqnode *next;

    TEqnode(){
        e = NULL;
        next = NULL;
    }

    TEqnode(FEqsys _e, TEqnode *_next){
        e = _e;
        next = _next;
    }

    ~TEqnode(){}

}TEqnode;

typedef TEqnode *ENodeptr;

ENodeptr insertFirstE(ENodeptr n, TEqnode fe);
ENodeptr remove_esearch(ENodeptr n);
bool isPresentE(ENodeptr n, string name);
ENodeptr insertE(ENodeptr n, string name);

ENodeptr command_new_system(ENodeptr n);
void command_print_system(ENodeptr n, string userinput);

#endif