#include "all-headers.h"
#include <iostream>
using namespace std;

// Methods

Tfmatrix::Tfmatrix() {
    nr = nc = 0;
}

Tfmatrix::Tfmatrix(int _nr, int _nc) {
    nr = _nr;
    nc = _nc;
    mat = new Fraction*[nr];
    for (int i = 0; i < nr; i++) {
        mat[i] = new Fraction[nc];
        for (int j = 0; j < nc; j++) {
            mat[i][j] = new Tfraction();
        }
    }
}

Tfmatrix::Tfmatrix(string _name, int _nr, int _nc) {
    nr = _nr;
    nc = _nc;
    name = _name;
    mat = new Fraction*[nr];
    for (int i = 0; i < nr; i++) {
        mat[i] = new Fraction[nc];
        for (int j = 0; j < nc; j++) {
            mat[i][j] = new Tfraction();
        }
    }
}

Tfmatrix::Tfmatrix(int _nr, int _nc, int min, int max) {
    nr = _nr;
    nc = _nc;
    mat = new Fraction*[nr];
    for (int i = 0; i < nr; i++) {
        mat[i] = new Fraction[nc];
        for (int j = 0; j < nc; j++) {
            mat[i][j] = fraction_simplification(
                mat[i][j] = new Tfraction(
                    rand() % (max - min + 1) + min,
                    1
                )
            );
        }
    }
}

void Tfmatrix::print() const {
    for (int i = 0; i < nr; i++) {
        for (int j = 0; j < nc; j++) {
            mat[i][j]->print(); printf("  ");
        }
        printf("\n");
    }
}

void Tfmatrix::init() {
    float coe;
    for (int i = 0; i < nr; i++) {
        for (int j = 0; j < nc; j++) {
            printf("insert in position [%d, %d]: ", i+1, j+1); scanf("%f", &coe);
            mat[i][j]->set(coe);
            mat[i][j] = fraction_simplification(mat[i][j]);
        }
    }
}

Tfmatrix::~Tfmatrix() {
    for (int i = 0; i < nr; i++) {
        for (int j = 0; j < nc; j++) {
            delete mat[i][j];
        }
        delete[] mat[i];
    }
    delete[] mat;
}

// Functions

FMatrix init_fmatrix() {
    int r, c;
    string name;
    cout << "name= "; cin >> name;
	cout << "rows= "; cin >> r;
	cout << "columns= "; cin >> c;
    cout << endl;
    FMatrix m = new Tfmatrix(name, r, c);
    Fraction f;

    string value;
    for(int i = 0; i < m->nr; i++){
        cout << "   ";
        for(int j = 0; j < m->nc; j++){
            cin >> value;
            //value = parse_fraction(value);
            f = str_to_fraction(value);
            m->mat[i][j]->num = f->num;
            m->mat[i][j]->den = f->den;
        }
    }
    cout << endl << endl;

    return m;
}

FMatrix fraction_matrix_transpose(FMatrix m) {
    FMatrix mT = new Tfmatrix(m->nc, m->nr);
    for (int i = 0; i < m->nr; i++) {
        for (int j = 0; j < m->nc; j++) {
            mT->mat[j][i] = m->mat[i][j];
        }
    }
    return mT;
}

FMatrix fraction_matrix_sum(FMatrix a, FMatrix b) {
    if (a->nr != b->nr || a->nc != b->nc) return new Tfmatrix();
    int r = a->nr, c = a->nc;
    FMatrix sum = new Tfmatrix(r, c);
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            sum->mat[i][j] = fraction_sum(a->mat[i][j], b->mat[i][j]);
        }
    }
    return sum;
}

FMatrix fraction_matrix_multiplication(FMatrix a, FMatrix b) {
    if(a->nc == b->nr){
        FMatrix multi = new Tfmatrix(a->nr, b->nc);
        for(int i = 0; i < multi->nr; i++){
            for(int j = 0; j < multi->nc; j++){
                for(int k = 0; k < multi->nc; k++){
                    multi->mat[i][j] = fraction_sum(
                        multi->mat[i][j], 
                        fraction_product(a->mat[i][k], b->mat[k][j])
                    );
                }
            }
        }
    return multi;
    } else {
        cout << "Impossible to multiply the given functions";
        return new Tfmatrix();
    }
}

FMatrix fraction_matrix_scalar_multiplication(FMatrix a, float lambda) {
    Fraction l = new Tfraction(lambda);
    for (int i=0; i<a->nr; i++) {
        for (int j=0; j<a->nc; j++) {
            a->mat[i][j] = fraction_product(l, a->mat[i][j]);
        }
    }
    return a;
}

void fraction_S(FMatrix m, int a, int b) {
    FVector v = new Tfvector(m->mat[a], m->nc);
    m->mat[a] = m->mat[b]; m->mat[b] = v->array;
}

void fraction_D(FMatrix m, int a, Fraction lambda) {
    for(int j = 0; j < m->nc; j++)
        m->mat[a][j] = fraction_product(m->mat[a][j], lambda);
}

void fraction_E(FMatrix m, int d, int s, Fraction lambda) { 
    FVector v = new Tfvector(m->mat[s], m->nc);
    v->multiply(lambda);
    for(int j = 0; j < m->nc; j++){
        m->mat[d][j] = fraction_sum(m->mat[d][j], v->array[j]);
    }
}

//void fraction_matrix_gauss_jordan(FMatrix m) {}