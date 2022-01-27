#include <iostream>
#include <ctime>
#include <bits/stdc++.h>
#include "all-headers.h"
using namespace std;

FNodeptr insertFirstF(FNodeptr n, Function f){
    return new TfunctionList(f, n);
}

Function get_fsearch(FNodeptr n, string name){
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

bool isPresentF(FNodeptr n, string name){
    if(n == NULL) return false;
    FNodeptr t = n;
    while(t != NULL){
        if(t->f->name == name){
            return true;
        }
        t = t->next;
    }
    return false;
}

FNodeptr insertF(FNodeptr n, string name){
    if(!isPresentF(n, name)){
        n = insertFirstF(n, init_function(name));
    } else {
        cout << "Function with the same name already exists" << endl << endl;
    }
    return n;
}

void command_print_function(FNodeptr n){
    string name; cout << "Function name: "; fflush(stdin); cin >> name;
    Function f = get_fsearch(n, name);
    if(f != NULL){
        print_function(f); cout << endl << endl;
    } else {
        cout << "No such function found" << endl << endl;
    }
}

void command_print_all_functions(FNodeptr n){
    if(n == NULL){
        cout << "No saved functions" << endl << endl; return;
    }
    FNodeptr t = n;
    while(t != NULL){
        print_function(t->f); cout << endl << endl;
        t = t->next;
    }
}

FNodeptr command_new_function_from_representative_matrix(FNodeptr n){
    string name; cout << "Function name: "; fflush(stdin); cin >> name;
    Function f = new Tfunction();
    if(! isPresentF(n, name)){
        f->name = name;
        f->mr = translate_linear_function(); f->mr->name = "M"; f->mr->name.append("(" + f->name + ")"); 
        f->b1 = id(f->mr->nc); f->b2 = id(f->mr->nr); 
        cout << endl; print_function(f); cout << endl;
        return insertFirstF(n, f);
    } else {
        cout << "Function with the same name already exists" << endl << endl;
    }
    return n;
}