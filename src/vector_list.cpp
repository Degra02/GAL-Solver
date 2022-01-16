#include <iostream>
#include <ctime>
#include <bits/stdc++.h>
#include "all-headers.h"
using namespace std;

VNodeptr insertFirstV(VNodeptr n, Vector v){
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

VNodeptr insertV(VNodeptr n, string name){
    if(! isPresentV(n, name)){
        n = insertFirstV(n, init_vector(name));
    } else {
        cout << endl << "Vector with the same name already present" << endl;
    }
    return n;
}