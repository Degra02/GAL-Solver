#include "all-headers.h"
#include <iostream>
using namespace std;

TsetFVectors::TsetFVectors(string _n){
    dim = 0; n_th = 0; name = _n;
}

TsetFVectors::TsetFVectors(int _dim, int _n_th){
    dim = _dim; n_th = _n_th; name = "";
    v = new Vector[dim];
    for(int i = 0; i < dim; ++i) v[i] = new Tfvector(n_th);
}

TsetFVectors::TsetFVectors(int x, int y, string _n){
    dim = x; n_th = y; name = _n; v = new Vector[dim];
    for(int i = 0; i < dim; ++i) v[i] = new Tfvector(n_th);
}

TsetFVectors::~TsetFVectors(){
    for(int i = 0; i < dim; ++i) delete v[i];
    delete[] v;
}

void TsetFVectors::print() const {
    cout << "{ ";
    for(int i = 0; i < dim; ++i){ 
        v[i]->print(); if (i != (dim - 1)) cout << ", "; 
    }
    cout << " }";
}

Set id(int dim){
    Set a = new TsetFVectors(dim, dim, "C" + to_string(dim));
    for(int i = 0; i < dim; i++){
        for(int j = 0; j < dim; j++){
            if(j == i){
                a->v[i]->array[j] = str_to_fraction("1");
            } else {
                a->v[i]->array[j] = str_to_fraction("0");
            }
        }
    }
    return a;
}

int parse_canonical_base(string name){
    int i = 0; string val = ""; 
    while(name[i] != '\0'){
        if(name[i] >= '0' && name[i] <= '9'){
            val += name[i];
        }
        ++i;
    }
    return stoi(val);
}

Set init_set_fvectors(string name){
    int _dim, _n_th;
    if(name[0] == 'C' && (name.length() > 1)){
        _dim = parse_canonical_base(name);
        Set i = id(_dim);
        print_set_fvectors(i); cout << endl; return i;
    } else {
        cout << "Vector size= "; cin >> _n_th; 
        cout << "Dimension= "; cin >> _dim; cout << endl;
        return insert_values_set_fvectors(_dim, _n_th, name);
    }
}

Set init_set_fvectors_base(string name){
    if(name[0] == 'C' && (name.length() > 1)){
        return id(parse_canonical_base(name));
    }
    int _dim, _n_th; Set base; bool m = false;
    cout << "Vector size= "; cin >> _n_th; _dim = _n_th;
    cout << endl;
    return init_base(_dim, _n_th, name);
}

Set init_set_fvectors_base_function(string name, int _n_th){
    if(name[0] == 'C' && (name.length() > 1)){
        return id(parse_canonical_base(name));
    }
    return init_base(_n_th, _n_th, name);
}

Set init_base(int _dim, int _n_th, string name){
    Set base; bool m = false;
    do{ 
        if(m) cout << "The set of vectors is not a base." << endl;
        base = insert_values_set_fvectors(_dim, _n_th, name); 
        m = true; 
    }while(!set_fvectors_is_base(base));
    return base;
}

Set insert_values_set_fvectors(int _dim, int _n_th, string name){
    Set sv = new TsetFVectors(_dim, _n_th, name); 
    string value;
    for(int i = 0; i < _dim; ++i){  
        cout << "V" << i + 1 << ":"; 
        sv->v[i] = new Tfvector(_n_th); 
        for(int j = 0; j < _n_th; ++j){
            cout << "  "; cin >> value; 
            sv->v[i]->array[j] = fraction_simplification(str_to_fraction(value)); 
        }
        cout << endl; 
    } 
    fflush(stdin);
    return sv;
}

void print_set_fvectors(Set sv){
    cout << "Name: " << "\x1b[38;5;50m" << sv->name << "\x1b[0m";
    cout << endl << endl; cout << "   "; sv->print();
    cout << endl << endl;
}

Matrix set_vectors_to_fmatrix(Set sv){
    Matrix m = new Tfmatrix(sv->n_th, sv->dim);
    for(int j = 0; j < m->nc; ++j){
        for (int i = 0; i < m->nr; ++i){
            m->mat[i][j] = fraction_copy(sv->v[j]->array[i]); 
        }
    }
    return m; 
}

bool set_fvectors_is_linearly_independent(Set sv) {
    int rank = fraction_matrix_rank(set_vectors_to_fmatrix(sv));
    return (rank == sv->dim);
}

bool set_fvectors_is_generators(Set sv) {
    int rank = fraction_matrix_rank(set_vectors_to_fmatrix(sv));
    return (rank == sv->n_th);
}

bool set_fvectors_is_base(Set sv) {
    int rank = fraction_matrix_rank(set_vectors_to_fmatrix(sv));
    return ((rank == sv->n_th) && (rank == sv->dim));
}

Set Gram_Schmidt(Set sv){
    int _dim = sv->dim, _n_th = sv->n_th, j;
    Set a = new TsetFVectors(_dim, _n_th, "");
    Vector u = new Tfvector(_n_th);
    if(!set_fvectors_is_linearly_independent(sv)){ 
        cout << "the set of vectors is not linearly independent." << endl;
        return sv; 
    } 
    a->v[0] = sv->v[0];
    for (int i = 1; i < _dim; ++i){
        j = i; 
        for (int h = 0; h < _n_th; ++h){
            u->array[h] = new Tfraction(0, 1); 
        } 
        do { 
            --j;
            u = fvector_sum(u, fvector_product_with_scalar(a->v[j], fraction_quotient(
                    fvector_scalar_product(a->v[j], sv->v[i]), 
                    fvector_norm_noroot(a->v[j])
                )
            ));
        }while(j != 0);
        a->v[i] = fvector_difference(sv->v[i], u); 
    }
    for(int i = 0; i < _dim; ++i){
        a->v[i] = fvector_normalization(a->v[i]);
    }
    return a;
}

Set orthogonal_complement(Set sv){
    Set res;
    if(!set_fvectors_is_linearly_independent(sv)){ 
        cout << "the set of vectors is not linearly independent." << endl; 
        return sv; 
    }
    if(set_fvectors_is_generators(sv)){ 
        return new TsetFVectors(""); 
    }
    sv = Gram_Schmidt(sv);
    Vector b = new Tfvector(sv->dim);
    for(int i = 0; i < sv->dim; ++i){
        b->array[i] = new Tfraction(0, 1);
    } 
    Matrix A = new Tfmatrix(sv->dim, sv->n_th);
    for (int i = 0; i < sv->dim; ++i){
        for (int j = 0; j < sv->n_th; ++j){
            A->mat[i][j] = sv->v[i]->array[j];
        }
    }
    FEqsys e = new Tfeqsys(A, b); 
    res = feq_sys_sol(e); res = Gram_Schmidt(res);
    return res;
}

Set completion_of_base(Set sv){
    int _n_th = sv->n_th, _dim = sv->dim, r, free_column = 0;
    Set res = new TsetFVectors(_n_th, _n_th, "");
    if(!set_fvectors_is_linearly_independent(sv)){ 
        cout << "the set of vectors is not linearly independent." << endl; 
        return NULL; 
    }
    if(set_fvectors_is_generators(sv)) return NULL; 
    Matrix m = set_vectors_to_fmatrix(sv);
    Matrix mid = new Tfmatrix(_n_th, _dim + _n_th); 
    for(int i = 0; i < _n_th; ++i){
        for(int j = 0; j < _dim; ++j){
            mid->mat[i][j] = m->mat[i][j];
        }
        for(int j = _dim; j < _dim + _n_th; ++j){
            if(i == (j - _dim)) mid->mat[i][j] = new Tfraction(1, 0);
            else mid->mat[i][j] = new Tfraction(0, 1);
        }
    }
    Matrix midg = fraction_matrix_gauss_jordan(mid);
    for(int j = 0; j < (_dim + _n_th); ++j){ 
        r = j - free_column; 
        if (r >= _n_th) break;
        if (midg->mat[r][j]->num == 0){
            ++free_column;
        } 
        else {
            for (int h = 0; h < mid->nr; ++h){
                res->v[r]->array[h] = mid->mat[h][j]; 
            } 
        } 
    }
    return res;
}