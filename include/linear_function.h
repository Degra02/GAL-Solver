#include <iostream>
#include "all-headers.h"
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

Function init_function(string name, Lists l);
Function init_function_from_saved(string name, Lists l);
void print_function(Function f);

#endif
