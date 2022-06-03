#include <iostream>
#include "all-headers.h"
#include <bits/stdc++.h>
using namespace std;

#ifndef __LINEAR_FUNCTION_H__
#define __LINEAR_FUNCTION_H__

typedef struct Tfunction{
    string name;
    Set b1, b2;
    Matrix mr;

    Tfunction(){
        name = "";
        b1 = b2 = NULL;
        mr = NULL;
    }

    Tfunction(string _name, Set _b1, Set _b2){
        name = _name; b1 = _b1; b2 = _b2;
    }

    Tfunction(string _name, Set _b1, Set _b2, Matrix _mr){
        name = _name;
        b1 = _b1; b2 = _b2; 
        mr = _mr;
    }

    ~Tfunction(){}

}Tfunction;

typedef Tfunction *Function;

Function init_function(string name);
void print_function(Function f);
Matrix translate_linear_function(int dim1, int dim2);
Vector parse_linear_function_input(vector <string> *fun, int dim);
void collect_linear_function(vector <string> *fun);

Set Ker(Function f);
Set Im(Function f);
Set Counter_Im(Function f, Vector v);

bool function_is_bijective(Function f);
Vector apply_linear_function(Function f, Vector v);

#endif
