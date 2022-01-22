#include <iostream>
#include <cstdlib>
#include "all-headers.h"
using namespace std;

SNodeptr insertFirstS(SNodeptr n, setFVectorsPtr b){
    return new Tbflist(b, n);
}

SNodeptr remove_ssearch(SNodeptr n){
    string name; cout << "Set name: "; fflush(stdin); cin >> name;
    if(n == NULL){
        return NULL;
    }
    SNodeptr t = n;
    if(n->b->name == name){
        t = t->next; delete n;
        return t;
    }
    while((t->next != NULL) && (t->next->b->name != name)){
        t = t->next;
    }
    if(t->next != NULL){
        SNodeptr r = t->next;
        t->next = t->next->next;
        delete r; return n;
    }
    return n;
}

setFVectorsPtr get_ssearch(SNodeptr n, string name){
    if(n == NULL){
        return NULL;
    }
    SNodeptr t = n;
    while(t != NULL){
        if(t->b->name == name){
            return t->b;
        }
        t = t->next;
    }
    return NULL;
}

bool isPresentS(SNodeptr n, string name){
    if(n == NULL){
        return false;
    }
    SNodeptr t = n;
    while(t != NULL){
        if(t->b->name == name){
            return true;
        }
        t = t->next;
    }
    return false;
}

SNodeptr insertS(SNodeptr n, string name){
    if(! isPresentS(n, name)){
        return insertFirstS(n, init_set_fvectors(name));
    } else {
        cout << "Set with the same name already present" << endl << endl;
    }
    return n;
}

void command_print_vectors_set(SNodeptr n){
    string userinput; cout << "Set name: "; fflush(stdin); cin >> userinput;
    setFVectorsPtr b = get_ssearch(n, userinput);
    if(b != NULL){
        cout << endl; b->print(); cout << endl << endl;
    } else {
        cout << "Set not found" << endl << endl;
    }
}

SNodeptr command_new_vectors_set(SNodeptr n){
    string name; cout << "Set name: "; fflush(stdin); cin >> name; 
    return insertS(n, name);
}

void command_set_is_base(SNodeptr n){
    string name; cout << "Set name: "; fflush(stdin); cin >> name;
    setFVectorsPtr a = get_ssearch(n, name);
    if(a != NULL){
        if(set_fvectors_is_base(a)){
            cout << "The set is a base of R" << a->n_th << endl << endl;
        } else {
            cout << "The set is not a base" << endl << endl;
        }
    } else {
        cout << "Set not found" << endl << endl;
    }
}

void command_set_is_independent(SNodeptr n){
    string name; cout << "Set name: "; fflush(stdin); cin >> name;
    setFVectorsPtr a = get_ssearch(n, name);
    if(a != NULL){
        if(set_fvectors_is_linearly_independent(a)){
            cout << "The set is l.independent" << endl << endl;
        } else {
            cout << "The set is not l.independent" << endl << endl;
        }
    } else {
        cout << "Set not found" << endl << endl;
    }
}

void command_set_is_generator(SNodeptr n){
    string name; cout << "Set name: "; fflush(stdin); cin >> name;
    setFVectorsPtr a = get_ssearch(n, name);
    if(a != NULL){
        if(set_fvectors_is_linearly_independent(a)){
            cout << "The set is generator of R" << a->n_th << endl << endl;
        } else {
            cout << "The set is not a generator of R" << a->n_th << endl << endl;
        }
    } else {
        cout << "Set not found" << endl << endl;
    }
}