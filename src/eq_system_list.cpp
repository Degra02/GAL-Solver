#include <iostream>
#include <ctime>
#include <bits/stdc++.h>
#include "all-headers.h"
using namespace std;

ENodeptr insertFirstE(ENodeptr n, FEqsys fe){
    return new TEqnode(fe, n);
}

ENodeptr remove_esearch(ENodeptr n){
    string name; cout << "System name: "; fflush(stdin); cin >> name;
    if(n == NULL){
        return NULL;
    }
    if(n->e->name == name){
        delete n;
        return NULL;
    }
    ENodeptr t = n;
    while(t->next != NULL){
        if(t->next->e->name == name){
            ENodeptr r = t->next;
            t->next = t->next->next;
            delete r;
            return n;
        }
    }
    
    return n;
}

bool isPresentE(ENodeptr n, string name){
    if(n == NULL){
        return false;
    }
    ENodeptr t = n;
    while(t != NULL){
        if(t->e->name == name){
            return true;
        }
    }
    return false;
}

FEqsys get_esearch(ENodeptr n, string name){
    if(n == NULL){
        return NULL;
    }
    ENodeptr t = n;
    while((t != NULL) && (t->e->name != name)){
        t = t->next;
    }
    if(t != NULL){
        return t->e;
    } else {
        return NULL;
    }
}

ENodeptr insertE(ENodeptr n, string name){
    if(!isPresentE(n, name)){
        n = insertFirstE(n, init_feqsys(name));
    } else {
        cout << "System with the same name already present" << endl << endl;
    }
    return n;
}

ENodeptr command_new_system(ENodeptr n){
    string name; cout << "Name= "; fflush(stdin); cin >> name;
    return insertE(n, name);
}

void command_print_system(ENodeptr n){
    string userinput; cout << "System name: "; fflush(stdin); cin >> userinput;
    FEqsys eq = get_esearch(n, userinput);
    string choice; FMatrix tmp;
    if(eq != NULL){
        tmp = to_fmatrix(eq); tmp->name = eq->name;
        cout << "Print format: "; fflush(stdin); cin >> choice;
        if(choice == "fraction"){
            print_fmatrix(tmp);
        } else if(choice == "float"){
            print_fmatrix_float(tmp);
        } else {
            cout << "Invalid print format" << endl << endl;
        }
    } else {
        cout << "System not found" << endl << endl;
    } 
}

ENodeptr command_system_solution(ENodeptr n){
    string userinput; cout << "System name: "; fflush(stdin); cin >> userinput;
    FEqsys eq = get_esearch(n, userinput); FEqsys sol;
    if(eq != NULL){
        sol = feq_sys_rref(eq);
        sol->name = eq->name + "S";
    } else {
        cout << "No such system" << endl << endl;
    }
    n = insertFirstE(n, sol);
    FMatrix m = to_fmatrix(sol);
    m->name = sol->name;
    print_fmatrix(m);

    return n;
}