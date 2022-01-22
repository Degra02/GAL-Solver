#include "all-headers.h"
#include <iostream>
using namespace std;

Tfbase::Tfbase(){
    dim = 0;
    name = "";
    n_th = 0;
    v = NULL;
}

Tfbase::Tfbase(int x, int th, string _n) {
    dim = x; name = _n; n_th = th;
    v = new FVector[dim];
    for (int i = 0; i < dim; ++i) {
        v[i] = new Tfvector(th);
    }
}

Tfbase::~Tfbase() {
    for (int i = 0; i < dim; ++i) {
        delete v[i];
    }
    delete[] v;
}

void Tfbase::print() const {
    cout << "{ ";
    for (int i = 0; i < dim; ++i) {
        v[i]->print();
        if (i != (dim - 1)) cout << ", ";
    }
    cout << " }";
}

FBase init_fbase(string name) {
    int d, g; string value;
    cout << "Vector size="; cin >> g;
    cout << "Dimension="; cin >> d;
    cout << endl;
    FBase b = new Tfbase(d, g, name);
    for(int i = 0; i < d; ++i) {
        cout << "V1: ";
        b->v[i] = new Tfvector(b->n_th);
        for(int j = 0; j < b->n_th; ++j){
            cout << "   ";
            cin >> value;
            b->v[i]->array[j] = str_to_fraction(value);
            b->v[i]->array[j] = fraction_simplification(b->v[i]->array[j]);
        }
        cout << endl;
    }
    fflush(stdin); 
    cout << endl;

    return b;
}

void print_fbase(FBase b) {
    cout << "Name: " << "\x1b[38;5;50m" << b->name << "\x1b[0m";
    cout << endl << endl;
    cout << "   "; b->print();
    cout << endl << endl;
}