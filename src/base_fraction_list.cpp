#include <iostream>
#include <cstdlib>
#include "all-headers.h"
using namespace std;

BNodeptr insertFirstB(BNodeptr n, FBase b){
    return new Tbflist(b, n);
}

BNodeptr remove_bsearch(BNodeptr n){
    string name; cout << "Base name: "; fflush(stdin); cin >> name;
    if(n == NULL){
        return NULL;
    }
    BNodeptr t = n;
    if(n->b->name == name){
        t = t->next; delete n;
        return t;
    }
    while((t->next != NULL) && (t->next->b->name != name)){
        t = t->next;
    }
    if(t->next != NULL){
        BNodeptr r = t->next;
        t->next = t->next->next;
        delete r; return n;
    }
    return n;
}

FBase get_bsearch(BNodeptr n, string name){
    if(n == NULL){
        return NULL;
    }
    BNodeptr t = n;
    while(t != NULL){
        if(t->b->name == name){
            return t->b;
        }
        t = t->next;
    }
    return NULL;
}

bool isPresentB(BNodeptr n, string name){
    if(n == NULL){
        return false;
    }
    BNodeptr t = n;
    while(t != NULL){
        if(t->b->name == name){
            return true;
        }
        t = t->next;
    }
    return false;
}

BNodeptr insertB(BNodeptr n, string name){
    if(! isPresentB(n, name)){
        return insertFirstB(n, init_fbase(name));
    } else {
        cout << "Base with the same name already present" << endl << endl;
    }
    return n;
}

void command_print_base(BNodeptr n){
    string userinput; cout << "Base name: "; fflush(stdin); cin >> userinput;
    FBase b = get_bsearch(n, userinput);
    if(b != NULL){
        print_fbase(b);
    } else {
        cout << "Base not found" << endl << endl;
    }
}

BNodeptr command_new_base(BNodeptr n){
    string name; cout << "Base name: "; fflush(stdin); cin >> name; 
    return insertB(n, name);
}


