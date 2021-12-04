#include <iostream>
#include <cstdlib>
#include <ctime>
#include "matrix.h"
#include "determinant.h"
using namespace std;

float det(Matrix m) {
    if (m->nr == m->nc) {
        if (m->nr == 1) return m->mat[0][0];
        if (m->nr == 2) return m->mat[0][0]*m->mat[1][1]-m->mat[0][1]*m->mat[1][0];

        float determinante = 0.0;
        // Defined the sub-matrix sub_m (n-1)x(n-1)
		Matrix sub_m = new Tmatrix(m->nr-1, m->nc-1); 

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

Matrix reverse_matrix_det(Matrix m) {
    if (reverse_matrix_validation(m)) {
        // definisco la mia matrice di cofattori e la sua sottomatrice
        Matrix mat_cofactor = new Tmatrix(m->nr, m->nc);
        Matrix sub_m = new Tmatrix(m->nr-1, m->nc-1); 
    
        for (int i=0; i<m->nr; i++) {
            for (int j=0; j<m->nc; j++) {
                // riempio la sottomatrice per trovare il suo det
                for (int r=0; r<m->nr; r++) {
                    for (int c=0; c<m->nc; c++) {
                        if (r != i) sub_m->mat[r<i ? r : r-1][c<j ? c : c-1] = m->mat[r][c]; 
                    }
                }
                // calcolo cofattore usando il determinante della sottomatrice
                mat_cofactor->mat[i][j] = pow(-1.0, i+j)*det(sub_m);
            }
        }
        return matrix_scalar_multiplication(matrix_transpose(mat_cofactor), 1/det(m));
    } else {
        cout << "matrice non invertibile" << endl;
        return m;
    }
}

bool reverse_matrix_validation(Matrix m) {
    return (det(m) != 0);
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

