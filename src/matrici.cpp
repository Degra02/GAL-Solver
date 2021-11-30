#include <iostream>
#include <cstdlib>
#include <ctime>
#include "matrici.h"
#include "determinanti.h"
#include "vettori.h"
using namespace std;

void matrix_sum(Tmatrice *sum, Tmatrice *a, Tmatrice *b){
    if(a->nr == b->nr && a->nc == b->nc){
        *sum = Tmatrice(a->nr, a->nc);
        sum->mat = new float *[sum->nr];
        for(int i = 0; i < sum->nr; i++){
            sum->mat[i] = new float [sum->nc];
            for(int j = 0; j < sum->nc; j++){
                sum->mat[i][j] = a->mat[i][j] + b->mat[i][j];
            }
        }

    } else {
        cout << "Somma possibile solo fra matrici con stesso numero di righe e colonne";
        exit(1);
    }
}

Tmatrice matrix_multiplication(Tmatrice *a, Tmatrice *b){

}
