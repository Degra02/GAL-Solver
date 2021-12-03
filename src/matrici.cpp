#include <iostream>
#include <cstdlib>
#include <ctime>
#include <bits/stdc++.h>
#include "matrici.h"
#include "determinanti.h"
#include "vettori.h"
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
    
    v->~Tvettore();
}

void gauss_jordan_stairs(Matrix m){
    int c = 0;
    float lambda = 0;

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
}

void rref(Matrix m){
    float lambda = 0;
    int c = m->nc-1;

    while(c >= 0){
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
    Matrix mT = new Tmatrix(m->nr, m->nc);
    for (int i=0; i<m->nr; i++) {
        for (int j=0; j<m->nc; j++) {
            mT->mat[j][i] = m->mat[i][j];
        }
    }

    return mT;
}

string findFraction(string s){
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
            string num = findFraction(to_string(m->mat[i][j]));
            cout << setw(10) << num;
        }
        cout << endl << endl;
    }
}
