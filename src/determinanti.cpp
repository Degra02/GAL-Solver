#include <iostream>
#include <cstdlib>
#include <ctime>
#include "matrici.h"
#include "determinanti.h"
using namespace std;

float det(Matrix m) {
    if (m->nr == m->nc) {
        if (m->nr == 1) return m->mat[0][0];
        if (m->nr == 2) return m->mat[0][0]*m->mat[1][1]-m->mat[0][1]*m->mat[1][0];

        float determinante = 0.0;
        // Defined the sub-matrix sub_m (n-1)x(n-1)
		Matrix sub_m = new Tmatrix(m->nr-1, m->nc-1); 
		sub_m->mat = new float*[sub_m->nr];
        for (int j=0; j<sub_m->nr; j++)
            *(sub_m->mat + j) = new float[sub_m->nc];

        // Fill the sub-matrix sub_m by removing the i-row and the 0-column of the m matrix
        for (int i=0; i<m->nr; i++) {
            for (int r=0; r<m->nr; r++) {
                for (int c=1; c<m->nc; c++) {
                    if (r != i) sub_m->mat[r<i ? r : r-1][c-1] = m->mat[r][c]; 
                }
			}

            // Laplace's theorem to calculate the determinant
            determinante += pow(-1.0, i)*m->mat[i][0]*det(sub_m);
        }
        return determinante;
    } else {
        cout << "Cannot calculate the matrix determinant" << endl;
        return 0.0;
    }
}

float sarrus(Matrix m){ // Sarrus' method to calculare the determinant
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
        printf("\nCannot use Sarrus' rule");
    }

    return 1;
}

