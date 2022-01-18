#include <iostream>
#include "all-headers.h"
using namespace std;

Fraction det(FMatrix m) {
    if (m->nr == m->nc) {
        if (m->nr == 1) return m->mat[0][0];
        if (m->nr == 2) return fraction_difference(
                fraction_product(m->mat[0][0], m->mat[1][1]),
                fraction_product(m->mat[0][1], m->mat[1][0])
            );

        Fraction determinante = new Tfraction(0, 1);
        // Defined the sub-matrix sub_m (n-1)x(n-1)
        FMatrix sub_m = new Tfmatrix(m->nr - 1, m->nc - 1); 

        // Fill the sub-matrix sub_m by removing the i-row and the 0-column of the m matrix
        for (int i = 0; i < m->nr; ++i) {
            for (int r = 0; r < m->nr; ++r) {
                for (int c = 1; c < m->nc; ++c) {
                    if (r != i) sub_m->mat[r < i ? r : r - 1][c - 1] = m->mat[r][c]; 
                }
            }
            // Laplace's theorem to calculate the determinant
            determinante = fraction_sum(
                determinante, 
                fraction_product(
                    fraction_product(fraction_power(new Tfraction(-1, 1), i), m->mat[i][0]), 
                    det(sub_m)
                )
            );
        }
        return determinante;
    } else {
        cout << "Cannot calculate the matrix determinant" << endl;
        exit(1);
    }
}
