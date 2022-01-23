#include <iostream>
#include <ctime>
#include <bits/stdc++.h>
#include "all-headers.h"
using namespace std;

FNodeptr insertFirstF(FNodeptr n, PFunction f){
    return new TfunctionList(f, n);
}

PFunction get_fsearch(FNodeptr n, string name){
    if(n == NULL){
        return NULL;
    }
    FNodeptr t = n;
    while( t != NULL ){
        if(t->f->name == name){
            return t->f;
        }
        t = t->next;
    }
    return NULL;
}

void command_print_function(FNodeptr n){
    string name; cout << "Function name: "; fflush(stdin); cin >> name;
    PFunction f = get_fsearch(n, name);
    if(f != NULL){
        
    } else {
        cout << "No such function found" << endl << endl;
    }
}