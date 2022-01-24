#include <iostream>
#include <ctime>
#include <bits/stdc++.h>
#include "all-headers.h"
using namespace std;

Lists command_system_build(Lists list){
    string mn; cout << "Matrix name: "; fflush(stdin); cin >> mn;
    FMatrix a = get_search(list->Mlist, mn);
    if(a == NULL){
        cout << "No such matrix" << endl << endl;
        return list;
    }
    string vn; cout << "Vector name: "; fflush(stdin); cin >> vn;
    FVector b = get_vsearch(list->Vlist, vn);
    if(b == NULL){
        cout << "No such vector" << endl << endl;
        return list;
    }
    if(b->n != a->nr){
        cout << "Invalid vector (wrong size)" << endl << endl;
        return list;
    }
    FMatrix c = fraction_matrix_copy(a);
    FVector d = fraction_vector_copy(b);
    FEqsys sys = new Tfeqsys(c, d);
    sys->name = a->name + b->name; 
    cout << "System name:" << "\x1b[38;5;50m" << sys->name << "\x1b[0m" << endl << endl;
    list->Eqlist = insertFirstE(list->Eqlist, sys);
    return list;
}

Lists command_save_function(Lists list){
    Function f =list->Flist->f;
    if(f != NULL){
        list->Mlist = insertFirst(list->Mlist, f->mr);
        list->Slist = insertFirstS(list->Slist, f->b1);
        list->Slist = insertFirstS(list->Slist, f->b2);
    } else {
        cout << "Function not found" << endl << endl;
    }
    return list;
}