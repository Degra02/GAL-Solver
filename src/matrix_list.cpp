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
        cout << "Matrix with the same name already saved" << endl << endl;
    }
    return n;
}

void command_print_matrix(MNodeptr n, string userinput){
    FMatrix m = get_search(n, userinput);
    string choice;
    cout << "type of print: "; fflush(stdin); cin >> choice;

    if(m != NULL){
        if(choice  == "fraction"){
            print_fmatrix(m);
        } else if(choice == "float"){
            print_fmatrix_float(m);
        } else {
            cout << endl << "invalid option" << endl << endl;
        }
    } else {
        cout << endl << "Matrix not found" << endl << endl;
    }
}

MNodeptr command_new_matrix(MNodeptr n){
    string name;
    cout << "name= "; fflush(stdin); cin >> name;
    return insertM(n, name);
}

MNodeptr command_matrix_product(MNodeptr n){
    string n1, n2;
    cout << "Matrix names: "; fflush(stdin); cin >> n1 >> n2;
    FMatrix m1, m2, res;
    m1 = get_search(n, n1); m2 = get_search(n, n2);
    if(m1 != NULL && m2 != NULL){
        res = fraction_matrix_multiplication(m1, m2);
        res->name = m1->name + "x" + m2->name;
    } else if(m1 == NULL){
        cout << "No such matrix with name " << n1 << endl << endl;
    } else if(m2 == NULL){
        cout << "No such matrix with name " << n2 << endl << endl;
    } else {
        cout << "No such matrixes" << endl << endl;
    }
    print_fmatrix(res);
    return insertFirst(n, res);
}

MNodeptr command_matrix_sum(MNodeptr n){
    string n1, n2;
    cout << "Matrix names: "; fflush(stdin); cin >> n1 >> n2;
    FMatrix m1, m2, res;
    m1 = get_search(n, n1); m2 = get_search(n, n2);
    if(m1 != NULL && m2 != NULL){
        res = fraction_matrix_sum(m1, m2);
        res->name = m1->name + "+" + m2->name;
    } else if(m1 == NULL){
        cout << "No such matrix with name " << n1 << endl << endl;
    } else if(m2 == NULL){
        cout << "No such matrix with name " << n2 << endl << endl;
    } else {
        cout << "No such matrixes" << endl << endl;
    }
    print_fmatrix(res);
    return insertFirst(n, res);
}

MNodeptr command_matrix_difference(MNodeptr n){
    string n1, n2;
    cout << "Matrix names: "; fflush(stdin); cin >> n1 >> n2;
    FMatrix m1, m2, res;
    m1 = get_search(n, n1); m2 = get_search(n, n2);
    if(m1 != NULL && m2 != NULL){
        res = fraction_matrix_difference(m1, m2);
        res->name = m1->name + "-" + m2->name;
    } else if(m1 == NULL){
        cout << "No such matrix with name " << n1 << endl << endl;
    } else if(m2 == NULL){
        cout << "No such matrix with name " << n2 << endl << endl;
    } else {
        cout << "No such matrixes" << endl << endl;
    }
    print_fmatrix(res);
    return insertFirst(n, res);
}

MNodeptr command_matrix_traspose(MNodeptr n){
    string name;
    cout << "Matrix name: "; fflush(stdin); cin >> name;
    FMatrix m1 = get_search(n, name);
    FMatrix t;
    if(m1 != NULL){
        t = fraction_matrix_transpose(m1);
        t->name = m1->name + "T";
    } else {
        cout << "No such matrix" << endl << endl;
    }
    print_fmatrix(t);
    return insertFirst(n, t);
}
