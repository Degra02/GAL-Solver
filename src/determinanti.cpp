#include <iostream>
#include <cstdlib>
#include <ctime>
#include "matrici.h"
#include "determinanti.h"
using namespace std;

float det(Matrix m) {
	printf("%f\n", *( *(m->mat + 0) + 0));
    if (m->nr == m->nc) {
        if (m->nr == 1) return m->mat[0][0];
        if (m->nr == 2) return m->mat[0][0]*m->mat[1][1]-m->mat[0][1]*m->mat[1][0];
		int sub_row, sub_col;
        float determinante = 0.0;
		Matrix sub_m = new Tmatrice(m->nr-1, m->nc-1); 
		sub_m->mat = new float*[sub_m->nr];
			for (int j=0; j<sub_m->nr; j++)
				*(sub_m->mat + j) = new float[sub_m->nc];
        for (int i=0; i<m->nr; i++) {
			// non posso definire sub_m all'itero del ciclo
            for (int r=0; r<m->nr; r++) {
                for (int c=1; c<m->nc; c++) {
                    if (r != i) {
						// condizione ? assegnamento1 : assegnamento2
						if (r<i) {
							sub_row=r;
						} else {
							sub_row=r-1;
						}
						sub_col=c-1;

						sub_m->mat[sub_row][sub_col]=2.0;
						printf("%f\n", sub_m->mat[sub_row][sub_col]);
						printf("%f\n", m->mat[r][c]);
						sub_m->mat[sub_row][sub_col] = m->mat[r][c]; 
						printf("%f\n", sub_m->mat[sub_row][sub_col]);

						// visualizzare indici di sub_m e m
						printf("indice riga=%d\n", sub_row);
						printf("indice colonna=%d\n", sub_col);
						printf("r=%d\n", r);
						printf("c=%d\n", c);
                    }
                }
			}
	
			// visualizzazione matrice sub_m
			sub_m->stampa();
            determinante += pow(-1.0, i)*m->mat[i][0]*det(sub_m);
			// error
			printf("%f\n", m->mat[i][0]); 
			printf("%f\n", pow(-1.0, i));
			printf("determinamnte=%f\n", determinante);

			// fino alla prima iterazione i calcoli sono corretti 
			// la funzione si blocca all'inizio della seconda iterazione
        }
        return determinante;
    } else {
        return 0.0;
    }
}

float sarrus(Matrix m){ // Metodo di Sarrus per il calcolo del determinante
    if(m->nr == m->nc && m->nc <= 3 && m->nc > 0){
        float det;
        float full[m->nr][m->nc*2];
        
        for(int i = 0; i < m->nr; i++){
            for(int j = 0; j < m->nc*2; j++){
                if(j < m->nr){
                    full[i][j] = *( *(m->mat + i) + j);
                } else {
                    full[i][j] = *( *(m->mat + i) + j - m->nc);
                }
            }
        }

        det = 0;
        for(int j = 0; j < ((m->nc*2) - 1); j++){
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

