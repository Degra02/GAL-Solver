#include <iostream>
#include <ctime>
#include <bits/stdc++.h>
#include <vector>
#include "all-headers.h"
using namespace std;

Function init_function(string name){
    string n1, n2, n3;
    cout << "From base: "; fflush(stdin); cin >> n1; setFVectorsPtr b1 = init_set_fvectors(n1);
    cout << "To base: "; fflush(stdin); cin >> n2; setFVectorsPtr b2 = init_set_fvectors(n2);
    //l->Slist = insertFirstS(l->Slist, b1); l->Slist = insertFirstS(l->Slist, b2);
    n3 = "M" + b1->name + b2->name + "(" + name + ")";
    cout << "Representative matrix" << endl;
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
    cout << "Base \"from\":  "; print_set_fvectors(f->b1); cout << endl;
    cout << "Base \"to\":  "; print_set_fvectors(f->b2); cout << endl;
    print_fmatrix(f->mr); cout << endl;
}

void collect_linear_function(vector <string> *fun){
    string input, call; fflush(stdin); getline(cin, input);
    stringstream check(input);
    while(getline(check, call, ' ')){
        fun->push_back(call);
    }
}

FMatrix translate_linear_function(){
    int dim1, dim2; cout << "Dim \"from\": "; fflush(stdin); cin >> dim1;
    cout << "Dim \"to\": "; fflush(stdin); cin >> dim2; cout << endl;
    vector <string> fun[dim2];
    for(int i = 0; i < dim2; i++){
        cout << "Coord." << i+1 << ": ";
        collect_linear_function(&fun[i]);
    }

    FVector v[dim2];
    v[0] = new Tfvector(dim1); v[1] = new Tfvector(dim1);
    for(int i = 0; i < dim2; i++){
        v[i] = parse_linear_function_input(&fun[i], dim1);
    }

    FMatrix m = new Tfmatrix(dim2, dim1);

    for(int i = 0; i < dim2; i++){
        for(int j = 0; j < dim1; j++){
            m->mat[i][j] = v[i]->array[j];
        }
    }

    m->name = "test"; // ! Cambia il nome

    return m;
}

FVector parse_linear_function_input(vector <string> *fun, int dim){
    int l = fun->size(), p = 0, j; 
    FVector v = new Tfvector(dim);
    string tmp, coef; char var = 'a';

    tmp = fun->at(0); int l2 = fun->at(0).size();
    for(j = 0; j < l2; j++){
        if(tmp[j] > 'a' && tmp[j] < 'z'){
            var = tmp[j];
        }
    }
    for(p = 0; p < (var - 'a'); p++){
        v->array[p] = str_to_fraction("0");
    }

    //(tmp[j] - 'a')

    for(int i = 0; i < l; i++){
        coef = "";
        tmp = fun->at(i);
        j = 0;
        while(tmp[j] != var){
            if(tmp[j] == '+'){
                j++;
            } else if(tmp[j] == '-'){
                coef += "-"; j++;
            } else {
                coef += tmp[j];
                j++;
            }
        }
        if(coef == ""){
            coef = "1";
        } else if(coef == "-"){
            coef = "-1";
        }
        var++;
        if(p < dim){
            v->array[p] = str_to_fraction(coef); 
            v->array[p] = fraction_simplification(v->array[p]);
            p++;
        } 
    }
    while(p < dim){
        v->array[p] = str_to_fraction("0"); p++;
    }

    return v;
}

setFVectorsPtr Ker(Function f) {
    int _n_th = f->b2->n_th;
    FVector b = new Tfvector(_n_th);
    for (int i = 0; i < _n_th; ++i) b->array[i] = new Tfraction(0, 1);
    FEqsys ef = new Tfeqsys(f->mr, b);
    return feq_sys_sol(ef);
}

