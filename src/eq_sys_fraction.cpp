#include <iostream>
#include <ctime>
#include <bits/stdc++.h>
#include "all-headers.h"
using namespace std;

// Functions

/* trasforma un sistema lineare in una matrice */
FMatrix to_fmatrix(FEqsys e){
    FMatrix m = new Tfmatrix(e->A->nr, e->A->nc + 1);
    for(int i = 0; i < m->nr; i++){
        for(int j = 0; j < m->nc; j++){
            if(j == (m->nc - 1)) m->mat[i][j] = e->b->array[i];
            else m->mat[i][j] = e->A->mat[i][j];
        }
    }
    m->name = e->name; 
    return m;
}

/* trafmorma una matrice in un sistema lineare */
FEqsys to_feqsys_from_matrix(FMatrix m){
    FEqsys res = new Tfeqsys(new Tfmatrix(m->nr, m->nc - 1), new Tfvector(m->nr));
    for(int i = 0; i < m->nr; i++){
        for(int j = 0; j < m->nc; j++){
            if (j == m->nc - 1) res->b->array[i] = m->mat[i][j];
            else res->A->mat[i][j] = m->mat[i][j];
        }
    }
    return res;
}

/* riduce a scalini un sistema lineare */
FEqsys feq_sys_rref(FEqsys e){
    FMatrix tmp = to_fmatrix(e);
    tmp = fraction_matrix_rref(tmp);
    return to_feqsys_from_matrix(tmp);
}

/* inizializza un sistema lineare */
FEqsys init_feqsys(string name){
    FEqsys eq = new Tfeqsys(); string value;
    cout << "Coefficients matrix:" << endl;
    eq->A = init_fmatrix("");
    cout << "Known terms vector:"; 
    eq->b = new Tfvector(eq->A->nr);
    for(int i = 0; i < eq->A->nr; i++){ 
        cout << "   "; cin >> value; 
        eq->b->array[i] = fraction_simplification(str_to_fraction(value)); 
    }
    cout << endl; 
    eq->name = name;
    return eq;
}

/* visualizza sul prompt una sistema lineare */
void print_feqsys(FEqsys e){
    FMatrix m = to_fmatrix(e);
    print_fmatrix_system(m);
}

/* dato un sistema lineare ridorma il tipo di risultato che può avere */
Trc Rouche_Capelli(FEqsys e){
    int n = e->A->nc, rankA = fraction_matrix_rank(e->A);
    int rankAb = fraction_matrix_rank(to_fmatrix(e));
    if(rankA != rankAb) return NO_RESULT;
    if(rankA == rankAb && rankAb < n){
        FMatrix m = fraction_matrix_rref(e->A); int i, zero_column = 0;
        for(int j = 0; j < m->nc; ++j){
            i = j - zero_column; 
            if(i == m->nr){
                for(int c = j; c < m->nc; ++c){
                    for(int r = 0; r < m->nr; ++r){
                        if(m->mat[r][c]->num != 0) return INF_RESULTS;
                    }
                }
                return ONE_RESULT;
            }
            if(m->mat[i][j]->num == 0) ++zero_column; 
            else if(m->mat[i][j]->num != 1) return INF_RESULTS; 
        }
        return ONE_RESULT;
    }
    return ONE_RESULT;
}

/* risolve un sistema lineare */
setFVectorsPtr feq_sys_sol(FEqsys e){
    Trc type_res = Rouche_Capelli(e);
    setFVectorsPtr res = new TsetFVectors("");
    if(type_res == NO_RESULT) return res;
    else if(type_res == INF_RESULTS){
        FMatrix m = fraction_matrix_rref(e->A); int rank = fraction_matrix_rank(m), c = m->nc;
        int pivot_column_position[rank], pivot_row_position[rank], free_var_column_position[c - rank]; 
        int count1 = 0, count2 = 0, count3 = 0;
        int i, free_column = 0, __dim_base = c - rank; res->dim = __dim_base;
        res->n_th = c; res->v = new FVector[__dim_base];
        for(int d = 0; d < __dim_base; ++d) res->v[d] = new Tfvector(c);
        for(int j = 0; j < c; ++j){
            if(rank > 0){ 
                i = j - free_column;
                if(m->mat[i][j]->num == 0){ 
                    ++free_column; free_var_column_position[count3++] = j;
                    continue; /* passa alla prossima colonna */ 
                }
                pivot_column_position[count1++] = j; pivot_row_position[count2++] = i;
            }
            rank--; 
            if(rank < 0) free_var_column_position[count3++] = j;
        } 
        count3 = 0;
        for(int d = 0; d < __dim_base; ++d){ 
            count1 = count2 = 0;
            for(int j = 0; j < c; ++j){
                if(j == pivot_column_position[count1]){ 
                    res->v[d]->array[j] = 
                        fraction_sum(
                            e->b->array[pivot_row_position[count2]], 
                            fraction_product(new Tfraction(-1, 1), m->mat[pivot_row_position[count2]][free_var_column_position[count3]])); 
                    ++count1; ++count2; 
                } 
                else { res->v[d]->array[j] = (free_var_column_position[count3] == j) ? new Tfraction(1, 1) : new Tfraction(0, 1); }
            } 
            ++count3;
        }
        return res; 
    } else {
        e = feq_sys_rref(e);
        res->dim = 1; res->v = new FVector[1];
        if(e->A->nc > e->b->n){
            int rankA = fraction_matrix_rank(e->A);
            int i, j = 0, zero_column = 0;
            res->n_th = e->A->nc;
            res->v[0] = new Tfvector(res->n_th);
            while(rankA > 0){
                i = j - zero_column;
                if(e->A->mat[i][j]->num == 0) {
                    res->v[0]->array[j] = new Tfraction(0, 1);
                    ++zero_column;
                } else {
                    res->v[0]->array[j] = e->b->array[i];
                    --rankA;
                }
                ++j; 
            }
            for(int rest = j; rest < res->n_th; ++rest){
                res->v[0]->array[rest] = new Tfraction(0, 1);
            }
        } else {
            res->n_th = e->b->n;
            res->v[0] = e->b;
        }  
        return res;
    }
}
