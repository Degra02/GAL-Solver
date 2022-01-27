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

FNodeptr insertFirstF(FNodeptr n, Function f);
Function get_fsearch(FNodeptr n, string name);
bool isPresentF(FNodeptr n, string name);
FNodeptr insertF(FNodeptr n, string name);
void command_print_function(FNodeptr n);
void command_print_all_functions(FNodeptr n);
FNodeptr command_new_function_from_representative_matrix(FNodeptr n);

#endif
