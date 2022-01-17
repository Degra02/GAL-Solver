#include <iostream>
#include <ctime>
#include <bits/stdc++.h>
#include "all-headers.h"
using namespace std;

VNodeptr insertFirstV(VNodeptr n, FVector v){
    return new TVnode(v, n);
}

bool isPresentV(VNodeptr n, string name){
    if(n == NULL){
        return false;
    }
    VNodeptr t = n;
    while((t != NULL)){
        if(t->v->name == name){
            return true;
        }
        t = t->next;
    }
    return false;
}

VNodeptr remove_vsearch(VNodeptr n){
    string name;
    cout << "Vector name: "; fflush(stdin); cin >> name;
    if(n == NULL){
        return NULL;
    }
    if(n->v->name == name){
        delete n; return NULL;
    }
    VNodeptr t = n;
    while((t->next != NULL) && (t->next->v->name != name)){
        t = t->next;
    }
    if(t->next != NULL){
        VNodeptr r = t->next;
        t->next = t->next->next;
        delete r;
        return n;
    }
    return n;
}


FVector get_vsearch(VNodeptr n, string name){
    if(n == NULL){
        return NULL;
    }
    VNodeptr t = n;
    while((t != NULL) && (t->v->name != name)){
        t = t->next;
    }
    if(t == NULL){
        return NULL;
    } else {
        return t->v;
    }

}

VNodeptr insertV(VNodeptr n, string name){
    if(! isPresentV(n, name)){
        n = insertFirstV(n, init_fvector(name));
    } else {
        cout << endl << "Vector with the same name already present" << endl << endl;
    }
    return n;
}

void command_print_vector(VNodeptr n, string userinput){
    FVector v = get_vsearch(n, userinput);
    if(v != NULL){
        print_fvector(v);
    } else {
        cout << "Vector not found" << endl << endl;
    }
}

VNodeptr command_new_vector(VNodeptr n){
    string name;
    cout << "Name= "; fflush(stdin); cin >> name;
    return insertV(n, name);
}