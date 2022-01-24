#include <iostream>
#include "all-headers.h"
using namespace std;

#ifndef __LINEAR_FUNCTION_LIST_H__
#define __LINEAR_FUNCTION_LIST_H__

typedef struct TfunctionList{
    Function f;
    TfunctionList *next;

    TfunctionList(){
        f = NULL;;
        next = NULL;
    }

    TfunctionList(Function _f, TfunctionList *_next){
        f = _f;
        next = _next;
    }

}TfunctionList;

typedef TfunctionList *FNodeptr;

Lists insertFirstF(Lists l, Function f);
Function get_fsearch(FNodeptr n, string name);
bool isPresentF(FNodeptr n, string name);
Lists insertF(Lists l, string name);
Lists command_new_function(Lists l);
void command_print_function(FNodeptr n);

#endif
