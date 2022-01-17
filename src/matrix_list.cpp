#include <iostream>
#include <cstdlib>
#include "all-headers.h"
using namespace std;

MNodeptr insertFirst(MNodeptr n, FMatrix m){
    return new TMnode(m, n);
}

MNodeptr remove_search(MNodeptr n){
    string name; 
    cout << "name= "; cin >> name;
    if(n == NULL){
        return NULL;
    }
    MNodeptr t = n;
    while((t->next != NULL) && (t->next->m->name != name)){
        t = t->next;
    }
    if(t->next != NULL){
        MNodeptr r = t->next;
        t->next = t->next->next;
        delete r;
        return n;
    }
    return n;
}

FMatrix get(MNodeptr n){
    return n->m;
}

FMatrix get_search (MNodeptr n, string name){ // returns the matrix with the given name, NULL otherwise
    if(n == NULL){
        return NULL;
    }
    MNodeptr t = n;
    while((t != NULL) && (t->m->name != name)){
        t = t->next;
    }
    if(t == NULL){
        return NULL;
    } else {
        return t->m;
    }  
}

bool isPresent(MNodeptr n, string name){
    if(n == NULL){
        return false;
    }
    MNodeptr t = n;
    while((t != NULL)){
        if(t->m->name == name){
            return true;
        }
        t = t->next;
    }
    return false;
}

MNodeptr insertM(MNodeptr n, string name){
    if(! isPresent(n, name)){
        n = insertFirst(n, init_fmatrix(name));
    } else {
        cout << "Matrix with same name already saved" << endl << endl;
    }
    return n;
}

void command_print_matrix(MNodeptr n, string userinput){
    FMatrix m = get_search(n, userinput);
    if(m != NULL){
        print_fmatrix(m);
    } else {
        cout << endl << "Matrix not found" << endl << endl;
    }
}

MNodeptr command_new_matrix(MNodeptr n){
    string name;
    cout << "name= "; cin >> name;
    return insertM(n, name);
}

