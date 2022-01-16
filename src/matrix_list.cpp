#include <iostream>
#include <cstdlib>
#include "all-headers.h"
using namespace std;

MNodeptr insertFirst(MNodeptr n, Matrix m){
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

Matrix get(MNodeptr n){
    return n->m;
}

Matrix get_search (MNodeptr n, string name){ // returns the matrix with the given name, NULL otherwise
    if(n == NULL){
        return NULL;
    }
    MNodeptr t = n;
    while((t != NULL) && (t->m->name != name)){
        t = t->next;
    }
    return t->m;
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
        n = insertFirst(n, init_matrix(name));
    } else {
        cout << "Matrix with same name already saved" << endl << endl;
    }
    return n;
}

