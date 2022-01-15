#include <iostream>
#include <cstdlib>
#include "all-headers.h"
using namespace std;

Nodeptr insertFirst(Nodeptr n, Matrix m){
    return new Tnode(m, n);
}

Nodeptr remove_search(Nodeptr n){
    string name; 
    cout << "name= "; cin >> name;
    if(n == NULL){
        return NULL;
    }
    Nodeptr t = n;
    while((t->next != NULL) && (t->next->m->name != name)){
        t = t->next;
    }
    if(t->next != NULL){
        Nodeptr r = t->next;
        t->next = t->next->next;
        delete r;
        return n;
    }
    return n;
}

Matrix get(Nodeptr n){
    return n->m;
}

Matrix get_search(Nodeptr n){ // returns the matrix with the given name, NULL otherwise
    string name; 
    cout << "name= "; cin >> name;
    if(n == NULL){
        return NULL;
    }
    Nodeptr t = n;
    while((t != NULL) && (t->m->name != name)){
        t = t->next;
    }
    return t->m;
}

bool isPresent(Nodeptr n, string name){
    if(n == NULL){
        return false;
    }
    Nodeptr t = n;
    while((t != NULL)){
        if(t->m->name == name){
            return true;
        }
        t = t->next;
    }
    return false;
}

Nodeptr insert(Nodeptr n){
    Matrix m = init_matrix();
    if(! isPresent(n, m->name)){
        n = insertFirst(n, m);
    } else {
        cout << "Matrix with same name already saved\n";
    }
    return n;
}

