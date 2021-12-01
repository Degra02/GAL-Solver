#include <iostream>
#include <cstdlib>
#include <ctime>
#include "matrici.h"
#include "determinanti.h"
#include "vettori.h"
using namespace std;

Matriceptr matrix_multiplication(Matriceptr a, Matriceptr b){
    Matriceptr multi;
    if(a->nc == b->nr){
        multi = new Tmatrice(a->nr, b->nc);
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
        cout << "Moltiplicazione non possibile fra queste due matrici";
        exit(1);
    }
}
