#include <iostream>
#include <cstdlib>
#include <ctime>
#include <bits/stdc++.h>
#include "all-headers.h"
using namespace std;

Matrix matrix_multiplication(Matrix a, Matrix b){
    Matrix multi;
    if(a->nc == b->nr){
        multi = new Tmatrix(a->nr, b->nc);
        for(int i = 0; i < multi->nr; i++){
            for(int j = 0; j < multi->nc; j++){
                multi->mat[i][j] = 0;
                for(int k = 0; k < multi->nc; k++){
                    multi->mat[i][j] += (a->mat[i][k])*(b->mat[k][j]);
                }
            }
        }
    return multi;

    } else {
        cout << "Impossible to multiply the given functions";
        exit(1);
    }
}

void S(Matrix m, int a, int b){
    Vector v = new Tvettore(m->mat[a], m->nc);
    m->mat[a] = m->mat[b];
    m->mat[b] = v->array;
}

void D(Matrix m, int a, float lambda){
    for(int j = 0; j < m->nc; j++){
        m->mat[a][j] = m->mat[a][j]*lambda;
    }
}

void E(Matrix m, int d, int s, float lambda){ // d = destination, s = source;
    Vector v = new Tvettore(m->mat[s], m->nc);
    v->multiply(lambda);
    for(int j = 0; j < m->nc; j++){
        m->mat[d][j] = m->mat[d][j] + v->array[j];
    }
}

bool is_stairs_form(Matrix m) {
    int zeroCounter = 0; 
    int highZero = 0;
    for (int i=1; i<m->nr; i++) {
        for (int j=0; j<m->nc; j++) {
            if (i == 1) {
                if (m->mat[i][j] == 0) {
                    zeroCounter++;
                    highZero = zeroCounter;
                } else {
                    zeroCounter = 0;
                    break; 
                }
            } else {
                if (m->mat[i][j] == 0) {
                    zeroCounter++;
                } else {
                    if (zeroCounter <= highZero) {
                        return false;
                    }
                    highZero = zeroCounter;
                    zeroCounter = 0;
                    break;
                }
            }
        }
    }

    return true;
}

void matrix_stairs_gauss_jordan(Matrix m){
    int c = 0;
    float lambda = 0.0;

    while(c < m->nc){
        for(int i = 0; i < m->nr; i++){
            if(m->mat[i][c]){
                for(int k = i+1; k < m->nr; k++){
                    if(m->mat[k][c]){
                        lambda = -(m->mat[k][c] / m->mat[i][c]);
                        E(m, k, i, lambda);
                    } else {
                        continue;
                    }
                }
                c++;
            } else {
                if(i < m->nr-1){
                    for(int k = i+1; k < m->nr; k++){
                        if(m->mat[k][c]){
                            S(m, k, i);
                        }
                    }
                }
                c++;
            }
        }
    }

    /*if (!is_stairs_form(m)) 
        matrix_stairs_gauss_jordan(m);*/
}

int rg(Matrix m) { 
    int counter = 0;
    Matrix m_copy = new Tmatrix;
    m_copy->copy_matrix(m);
    matrix_stairs_gauss_jordan(m_copy);
    for (int i=0; i<m_copy->nr; i++) {
        for (int j=0; j<m_copy->nc; j++) {
            if (m_copy->mat[i][j] != 0.0) {
                counter++;
                j = m_copy->nc;
            }
        }
    }
    return counter;
}

void matrix_rref_calculator(Matrix m){
    float lambda = 0;
    int c = m->nc-1;

    while(c > 0){
        for(int i = m->nr - 1; i >= 0; i--){
            for(int k = i-1; k >= 0; k--){
                if(m->mat[k][c]){
                    lambda = -(m->mat[k][c] / m->mat[i][c]);
                    E(m, k, i, lambda);
                } else {
                    continue;
                }
            }
            c--; 
        }
    }
    int k = 0;
    for(int i = 0; i < m->nr; i++){
        lambda = (1 / m->mat[i][k]);
        D(m, i, lambda);
        k++;
    }
}

Matrix matrix_rref_full(Matrix m){
    Matrix temp = new Tmatrix();
    temp->copy_matrix(m);
    matrix_stairs_gauss_jordan(temp);
    matrix_rref_calculator(temp);

    return temp;
}

Matrix matrix_scalar_multiplication(Matrix a, float lambda) {
    for (int i=0; i<a->nr; i++) {
        for (int j=0; j<a->nc; j++) {
            a->mat[i][j] = lambda*a->mat[i][j];
        }
    }

    return a;
}

Matrix matrix_transpose(Matrix m) {
    Matrix mT = new Tmatrix(m->name + "T", m->nr, m->nc);
    for (int i=0; i<m->nr; i++) {
        for (int j=0; j<m->nc; j++) {
            mT->mat[j][i] = m->mat[i][j];
        }
    }

    return mT;
}

string parse_fraction(string s){
    // Initialize variables
    string be_deci = "", af_deci = "";
    bool x = true, y = false;
 
    // Traverse the floating string
    for (int i = 0; i < s.size(); ++i) {
        if (s[i] == '.') { // Check if decimal part exist
            x = false;
            y = true;
            continue;
        }

        // Retrieve decimal part
        if (x) 
            be_deci += s[i];
 
        if (y)
            af_deci += s[i];
    }
 
    // Convert string to integer
    int num_be_deci = stoi(be_deci);
    int num_af_deci = 0;
 
    // If no recurrence sequence exist
    if (af_deci.size() != 0)
        num_af_deci = stoi(af_deci);
 
    // Initialize numerator & denominator
    int numr = num_be_deci * pow(10, af_deci.size()) + num_af_deci;
 
    int deno = pow(10, af_deci.size());
    int gd = __gcd(numr, deno);
    
    string num = to_string(numr/gd);
    string den = to_string(deno/gd);

    if((numr == 0) || ((deno/gd) == 1)){
        return num;
    } else {
        string full = num.append("/").append(den);
        return full;
    }
    
    
    // Print the result
    /*if(deno == gd){
        cout << numr / gd;
    } else{
        cout << numr / gd << "/" << deno / gd;
    }*/
    
}

void print_fract_matrix(Matrix m){
    for(int i = 0; i < m->nr; i++){
        for(int j = 0; j < m->nc; j++){
            string num = parse_fraction(to_string(m->mat[i][j]));
            cout << setw(10) << num;
        }
        cout << endl << endl;
    }
}

Matrix init_matrix(){
    int r, c;
    string name;
    cout << "name= "; cin >> name;
	cout << "rows= "; cin >> r;
	cout << "columns= "; cin >> c;
    cout << endl;
    Matrix m = new Tmatrix(name, r, c);
    for(int i = 0; i < m->nr; i++){
        cout << "   ";
        for(int j = 0; j < m->nc; j++){
            scanf("%f", &m->mat[i][j]);
        }
    }
    cout << endl << endl;
    return m;
}

void print_matrix(Matrix m){
    cout << "Name: " << "\x1b[38;5;50m" << m->name << "\x1b[0m";
    cout << endl << endl;

    for(int i = 0; i < m->nr; i++){
        for(int j = 0; j < m->nc; j++){
            if(m->mat[i][j] == 0){
                printf("\x1b[38;5;239m %3d \x1b[0m",0);
            } else {
                if(m->mat[i][j] == (int)m->mat[i][j]){
                    printf(" %3.0f ", m->mat[i][j]);
                } else {
                    printf(" %3.1f ", m->mat[i][j]);
                }
            }
        }
        cout << endl;
    }
    cout << endl << endl;
}