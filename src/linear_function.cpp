#include <iostream>
#include <ctime>
#include <bits/stdc++.h>
#include "all-headers.h"
using namespace std;

Function init_function(string name){
    string n1, n2, n3;
    cout << "From base: "; fflush(stdin); cin >> n1; setFVectorsPtr b1 = init_set_fvectors(n1);
    cout << "To base: "; fflush(stdin); cin >> n2; setFVectorsPtr b2 = init_set_fvectors(n2);
    //l->Slist = insertFirstS(l->Slist, b1); l->Slist = insertFirstS(l->Slist, b2);
    n3 = "M" + b1->name + b2->name + "( " + name + " )";
    FMatrix m = init_fmatrix(n3);
    return new Tfunction(name, b1, b2, m);
}

/*Function init_function_from_saved(string name, Lists l){
    string n1, n2, n3;
    cout << "From base: "; fflush(stdin); cin >> n1;
    cout << "To base: "; fflush(stdin); cin >> n2;
    setFVectorsPtr b1 = get_ssearch(l->Slist, n1), b2 = get_ssearch(l->Slist, n2);
    if((b1 == NULL) || (b2 == NULL)){
        cout << "Base not found" << endl << endl; return NULL;
    }
    cout << "Representative matrix name: "; fflush(stdin); cin >> n3;
    FMatrix m1 = get_search(l->Mlist, n3);
    if(m1 == NULL){
        cout << "Matrix not found" << endl << endl; return NULL;
    }
    FMatrix m2 = fraction_matrix_copy(m1);
    m2->name = "M" + b1->name + b2->name + "( " + name + " )";
    return new Tfunction(name, b1, b2, m2);
}*/

void print_function(Function f){
    cout << f->name << endl;
    cout << "Base \"from\""; print_set_fvectors(f->b1); cout << endl;
    cout << "Base \"to\""; print_set_fvectors(f->b2); cout << endl;
    print_fmatrix(f->mr); cout << endl;
}