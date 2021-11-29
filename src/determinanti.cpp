#include <iostream>
#include <cstdlib>
#include <ctime>
#include "matrici.h"
#include "determinanti.h"
using namespace std;

float sarrus(Matrice m){
    if(m.nr == m.nc && m.nc <= 3 && m.nc > 0){
        float det;
        float full[m.nr][m.nc*2];
        
        for(int i = 0; i < m.nr; i++){
            for(int j = 0; j < m.nc*2; j++){
                if(j < m.nr){
                    full[i][j] = *((m.mat + i) + j);
                } else {
                    full[i][j] = *((m.mat + i) + j - m.nc);
                }
                printf("%5.1f", full[i][j]);
            }
            printf("\n");
        }
        det = 0;
        for(int j = 0; j < ((m.nc*2) - 1); j++){
            if(j <= 2){
                det += (full[0][j]*full[1][j+1]*full[2][j+2]);
            } 
            if(j >= 2){
                det -= (full[0][j]*full[1][j-1]*full[2][j-2]);
            }
        }
        
        return det;
    } else {
        printf("\nRegola di Sarrus non applicabile");
    }

    return 1;
}