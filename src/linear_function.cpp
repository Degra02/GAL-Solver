#include <iostream>
#include <ctime>
#include <bits/stdc++.h>
#include <vector>
#include "all-headers.h"
using namespace std;

Function init_function(string name){
    string n1, n2, n3;
    cout << "From base: "; fflush(stdin); cin >> n1; setFVectorsPtr b1 = init_set_fvectors_base(n1);
    cout << "To base: "; fflush(stdin); cin >> n2; setFVectorsPtr b2 = init_set_fvectors_base(n2);
    //l->Slist = insertFirstS(l->Slist, b1); l->Slist = insertFirstS(l->Slist, b2);
    n3 = "M" + b1->name + "->" + b2->name + "(" + name + ")";
    cout << "Representative matrix" << endl;
    FMatrix m = init_predefinition_fmatrix(n3, b2->n_th, b1->n_th);
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
    cout << "Name: " << f->name << endl << endl;
    cout << "Base \"from\":  "; print_set_fvectors(f->b1); cout << endl;
    cout << "Base \"to\":  "; print_set_fvectors(f->b2); cout << endl;
    print_fmatrix(f->mr); cout << endl;
}

// support function to save the user input
void collect_linear_function(vector <string> *fun){
    string input, call; fflush(stdin); getline(cin, input);
    stringstream check(input);
    while(getline(check, call, ' ')){
        fun->push_back(call);
    }
}

// Takes a linear function in the expression form and return the representative matrix
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

    return m; // TODO: add name (outside of this function)
}

FVector parse_linear_function_input(vector <string> *fun, int dim){
    int l = fun->size(), p = 0, j; 
    FVector v = new Tfvector(dim);
    string tmp, coef; char var = 'a';

    // checking at which variable the polynomial starts (default = a)
    tmp = fun->at(0); int l2 = fun->at(0).size();
    for(j = 0; j < l2; j++){
        if(tmp[j] > 'a' && tmp[j] < 'z'){
            var = tmp[j];
        }
    }
    for(p = 0; p < (var - 'a'); p++){
        v->array[p] = str_to_fraction("0");
    }

    // parsing the various strings contained in the vector "fun"
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
                coef += tmp[j]; j++;
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

setFVectorsPtr Im(Function f) {
    FMatrix mrg = fraction_matrix_gauss_jordan(f->mr);
    int rank = fraction_matrix_rank(mrg), i, zero_column = 0;
    setFVectorsPtr im = new TsetFVectors(rank, f->b2->n_th, "");
    for (int j = 0; j < mrg->nc; ++j) 
    { i = j - zero_column; if (i >= mrg->nc) break;
    if (mrg->mat[i][j]->num == 0) ++zero_column;
    else { --rank; for (int h = 0; h < mrg->nr; ++h) im->v[i]->array[h] = f->mr->mat[h][j]; } } 
    return im;
}

bool function_is_bijective(Function f) {
    setFVectorsPtr im = Im(f), ker = Ker(f);
    return set_fvectors_is_base(im) && ker->dim == 0;
}