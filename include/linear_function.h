#include <iostream>
#include "all-headers.h"
#include <bits/stdc++.h>
using namespace std;

#ifndef __LINEAR_FUNCTION_H__
#define __LINEAR_FUNCTION_H__

typedef struct Tfunction{
    string name;
    setFVectorsPtr b1, b2;
    FMatrix mr;

    Tfunction(){
        name = "";
        b1 = b2 = NULL;
        mr = NULL;
    }

    Tfunction(string _name, setFVectorsPtr _b1, setFVectorsPtr _b2, FMatrix _mr){
        name = _name;
        b1 = _b1; b2 = _b2; 
        mr = _mr;
    }

    ~Tfunction(){}

}Tfunction;

typedef Tfunction *Function;

Function init_function(string name);
//Function init_function_from_saved(string name, Lists l);
void print_function(Function f);
FMatrix translate_linear_function();
FVector parse_linear_function_input(vector <string> *fun, int dim);
void collect_linear_function(vector <string> *fun);

setFVectorsPtr Ker(Function f);
setFVectorsPtr Im(Function f);

bool function_is_bijective(Function f);

#endif
