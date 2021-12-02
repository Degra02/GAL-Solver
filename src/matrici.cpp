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
    Vector v = new Tvettore(m->mat[a-1], m->nc);
    m->mat[a-1] = m->mat[b-1];
    m->mat[b-1] = v->array;
}

void D(Matrix m, int a, float lambda){
    for(int j = 0; j < m->nc; j++){
        m->mat[a-1][j] = m->mat[a-1][j]*lambda;
    }
}

void E(Matrix m, int d, int s, float lambda){ // d = destination, s = source;
    Vector v = new Tvettore(m->mat[s-1], m->nc);
    v->multiply(lambda);
    for(int j = 0; j < m->nc; j++){
        m->mat[d-1][j] = m->mat[d-1][j] + v->array[j];
    }
    
    v->~Tvettore();
}

Matrix matrix_scalat_multiplication(Matrix a, float lambda) {
    for (int i=0; i<a->nr; i++) {
        for (int j=0; j<a->nc; j++) {
            a->mat[i][j] = lambda*a->mat[i][j];
        }
    }

    return a;
}

Matrix matrix_transpose(Matrix m) {
    Matrix T = new Tmatrix(m->nr, m->nc);
    for (int i=0; i<m->nr; i++) {
        for (int j=0; j<m->nc; j++) {
            T->mat[j][i] = m->mat[i][j];
        }
    }

    return T;
}

void print_fract_matrix(Matrix m){
    for(int i = 0; i < m->nr; i++){
        for(int j = 0; j < m->nc; j++){
            cout << "   "; findFraction(to_string(m->mat[i][j]));
        }
        cout << endl << endl;
    }
}

void findFraction(string s){
    // Initialize variables
    string be_deci = "",
           af_deci = "",
           reccu = "";
 
    bool x = true, y = false,
         z = false;
 
    // Traverse the floating string
    for (int i = 0; i < s.size(); ++i) {
 
        // Check if decimal part exist
        if (s[i] == '.') {
            x = false;
            y = true;
            continue;
        }
 
        // Check if recurrence
        // sequence exist
        if (s[i] == '(') {
            z = true;
            y = false;
            continue;
        }
 
        // Retrieve decimal part
        // and recurrence re sequence
        if (x)
            be_deci += s[i];
 
        if (y)
            af_deci += s[i];
 
        if (z) {
 
            // Traverse the string
            for (; i < s.size()
                   && s[i] != ')';
                 ++i)
                reccu += s[i];
            break;
        }
    }
 
    // Convert string to integer
    int num_be_deci = stoi(be_deci);
    int num_af_deci = 0;
 
    // If no recurrence sequence exist
    if (af_deci.size() != 0)
        num_af_deci = stoi(af_deci);
 
    // Initialize numerator & denominator
    int numr = num_be_deci
                   * pow(10, af_deci.size())
               + num_af_deci;
 
    int deno = pow(10, af_deci.size());
 
    // No reccuring term
    if (reccu.size() == 0) {
        int gd = __gcd(numr, deno);
 
        // Print the result
        cout << numr / gd << "/"
             << deno / gd;
    }
 
    // If reccuring term exist
    else {
 
        // Convert reccuring term to integer
        int reccu_num = stoi(reccu);
 
        // reccu.size() is num of
        // digit in reccur term
        int numr1
            = numr
                  * pow(10, reccu.size())
              + reccu_num;
 
        int deno1 = deno
                    * pow(10, reccu.size());
 
        // eq 2 - eq 1
        int res_numr = numr1 - numr,
            res_deno = deno1 - deno;
 
        int gd = __gcd(res_numr,
                       res_deno);
 
        // Print the result
        cout << res_numr / gd << "/"
             << res_deno / gd;
    }
}