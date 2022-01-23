#include "all-headers.h"
#include <iostream>
using namespace std;

TsetFVectors::TsetFVectors(string _n) {
    dim = 0; n_th = 0; 
    name = _n;
}

TsetFVectors::TsetFVectors(int x, int y, string _n) {
    dim = x; n_th = y;
    name = _n;
    v = new FVector[dim];
    for (int i = 0; i < dim; ++i) {
        v[i] = new Tfvector(n_th);
    }
}

TsetFVectors::~TsetFVectors() {
    for (int i = 0; i < dim; ++i) {
        delete v[i];
    } 
    delete[] v;
}

void TsetFVectors::print() const {
    cout << "{ ";
    for (int i = 0; i < dim; ++i) {
        v[i]->print();
        if (i != (dim - 1)) cout << ", ";
    }
    cout << " }";
}

setFVectorsPtr init_set_fvectors(string name) {
    string value;
    int _dim, _n_th;
    
    cout << "Vector size= "; cin >> _n_th;
    cout << "Dimension= "; cin >> _dim;
    cout << endl;

    setFVectorsPtr sv = new TsetFVectors(_dim, _n_th, name);
    for(int i = 0; i < _dim; ++i) {
        cout << "V" << (i + 1) << ":";
        sv->v[i] = new Tfvector(_n_th);
        for(int j = 0; j < _n_th; ++j) {
            cout << "  "; cin >> value;
            sv->v[i]->array[j] = str_to_fraction(value);
            sv->v[i]->array[j] = fraction_simplification(sv->v[i]->array[j]);
        }

        cout << endl;
    }

    cout << endl;
    fflush(stdin); 
    return sv;
}

void print_set_fvectors(setFVectorsPtr sv) {
    cout << "Name: " << "\x1b[38;5;50m" << sv->name << "\x1b[0m";
    cout << endl << endl;

    cout << "   "; sv->print();

    cout << endl << endl;
}

FMatrix set_vectors_to_fmatrix(setFVectorsPtr sv) {
    FMatrix m = new Tfmatrix(sv->n_th, sv->dim);
    for (int j = 0; j < m->nc; ++j) {
       for (int i = 0; i < m->nr; ++i) {
           m->mat[i][j] = sv->v[j]->array[i];
       }
    }

    return m;
}

bool set_fvectors_is_linearly_independent(setFVectorsPtr sv) {
    int rank = fraction_matrix_rank(set_vectors_to_fmatrix(sv));
    return (rank == sv->dim);
}

bool set_fvectors_is_generators(setFVectorsPtr sv) {
    int rank = fraction_matrix_rank(set_vectors_to_fmatrix(sv));
    return (rank == sv->n_th);
}

bool set_fvectors_is_base(setFVectorsPtr sv) {
    int rank = fraction_matrix_rank(set_vectors_to_fmatrix(sv));
    return ((rank == sv->n_th) && (rank == sv->dim));
}

setFVectorsPtr Gram_Schmidt(setFVectorsPtr sv) {
    int _dim = sv->dim, _n_th = sv->n_th;
    int j;
    setFVectorsPtr a = new TsetFVectors(_dim, sv->n_th, "");
    FVector u = new Tfvector(_n_th);
    for (int i = 0; i < _n_th; ++i) u->array[i] = new Tfraction(0, 1);

    if (!set_fvectors_is_linearly_independent(sv)) {
        cout << "the set of vectors is not linearly independent." << endl;
        return sv;
    } 

    a->v[0] = sv->v[0]; 
    for (int i = 1; i < _dim; ++i) {
        j = i;
        do {
            --j;
            u = fvector_sum(u, fvector_product_with_scalar(a->v[j], fraction_quotient(
                fvector_scalar_product(a->v[j], sv->v[i]),
                fvector_norm_noroot(a->v[j])
            )));
        } while (j != 0);
        a->v[i] = fvector_difference(sv->v[i], u);
    }

    return a;
}