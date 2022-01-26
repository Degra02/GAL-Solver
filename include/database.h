#include <iostream>
#include "matrix_list.h"
#include "vector_list.h"
#include "eq_system_list.h"
#include "base_fraction_list.h"
#include "linear_function_list.h"
using namespace std;

#ifndef __DATABASE_H__
#define __DATABASE_H__

typedef struct Tlists{
    MNodeptr Mlist;
    VNodeptr Vlist;
    ENodeptr Eqlist;
    SNodeptr Slist;
    FNodeptr Flist;

    Tlists(){
        Mlist = NULL;
        Vlist = NULL;
        Eqlist = NULL;
        Slist = NULL;
        Flist = NULL;
    }

    ~Tlists(){}

}Tlists;

typedef Tlists *Lists;

Lists command_system_build(Lists list);
Lists command_save_function(Lists list);
Lists command_apply_function(Lists list);

#endif
