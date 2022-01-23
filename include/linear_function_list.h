#include <iostream>
#include "all-headers.h"
using namespace std;

#ifndef __LINEAR_FUNCTION_LIST_H__
#define __LINEAR_FUNCTION_LIST_H__

typedef struct TfunctionList{
    PFunction f;
    TfunctionList *next;

    TfunctionList(){
        f = NULL;;
        next = NULL;
    }

    TfunctionList(PFunction _f, TfunctionList *_next){
        f = _f;
        next = _next;
    }

}TfunctionList;

typedef TfunctionList *FNodeptr;

FNodeptr insertFirstF(FNodeptr n, PFunction f);
PFunction get_fsearch(FNodeptr n, string name);
void command_print_function(FNodeptr n);

#endif
