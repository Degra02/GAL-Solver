#include <iostream>
#include <ctime>
#include <bits/stdc++.h>
#include "all-headers.h"
using namespace std;

// Functions

/* turns a linear equations system into a matrix */
Matrix to_fmatrix(FEqsys e){
    Matrix m = new Tfmatrix(e->A->nr, e->A->nc + 1);
    for(int i = 0; i < m->nr; i++){
        for(int j = 0; j < m->nc; j++){
            if(j == (m->nc - 1)) m->mat[i][j] = e->b->array[i];
            else m->mat[i][j] = e->A->mat[i][j];
        }
    }
    m->name = e->name; 
    return m;
}

/* turns a matrix into a linear equations sytem */
FEqsys to_feqsys_from_matrix(Matrix m){
    FEqsys res = new Tfeqsys(new Tfmatrix(m->nr, m->nc - 1), new Tfvector(m->nr));
    for(int i = 0; i < m->nr; i++){
        for(int j = 0; j < m->nc; j++){
            if (j == m->nc - 1) res->b->array[i] = m->mat[i][j];
            else res->A->mat[i][j] = m->mat[i][j];
        }
    }
    return res;
}

/* rref form of a linear equations system */
FEqsys feq_sys_rref(FEqsys e){
    Matrix tmp = to_fmatrix(e);
    tmp = fraction_matrix_rref(tmp);
    return to_feqsys_from_matrix(tmp);
}

/* linear equation system init */
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

/* prints a linear equation system on the console buffer */
void print_feqsys(FEqsys e){
    Matrix m = to_fmatrix(e);
    print_fmatrix_system(m);
}

/* given a linear equations system returns the class of solution of that system */
Trc Rouche_Capelli(FEqsys e){
    int n = e->A->nc, rankA = fraction_matrix_rank(e->A);
    int rankAb = fraction_matrix_rank(to_fmatrix(e));
    if(rankA != rankAb) return NO_RESULT;
    if(rankA == rankAb && rankAb < n){
        Matrix m = fraction_matrix_rref(e->A); int i, zero_column = 0;
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

setFVectorsPtr set_base_inf_sol(FEqsys e, FreeColumnsPtr fc, PivotRowsColumnsPtr pcr){
    e = feq_sys_rref(e);
    Matrix m = e->A; 
    int num_columns = m->nc;
    setFVectorsPtr res = new TsetFVectors(fc->dim, num_columns);
    int fc_counter, pcr_counter;
    fc_counter = pcr_counter = 0;
    for(int d = 0; d < res->dim; ++d){ 
        for(int j = 0; j < num_columns; ++j){
            if(j == pcr->pivot_columns[pcr_counter]){ 
                res->v[d]->array[j] = 
                    fraction_sum(e->b->array[pcr->pivot_rows[pcr_counter]], fraction_product(
                            new Tfraction(-1, 1), 
                            m->mat[pcr->pivot_rows[pcr_counter]][fc->free_columns[fc_counter]]
                        )
                    ); 
                ++pcr_counter; 
            } 
            else { 
                res->v[d]->array[j] = 
                    (fc->free_columns[fc_counter] == j) ? new Tfraction(1, 1) : new Tfraction(0, 1); 
            }
        } 
        ++fc_counter;
    }
    return res; 
}

setFVectorsPtr feq_sys_inf_sol(FEqsys e){
    if (Rouche_Capelli(e) != INF_RESULTS) exit(1);
    Matrix m = fraction_matrix_rref(e->A); 
    FreeColumnsPtr fc = free_columns(m);
    PivotRowsColumnsPtr pcr = pivot_rows_columns(m);
    return set_base_inf_sol(e, fc, pcr);
}

setFVectorsPtr feq_sys_one_sol(FEqsys e){
    if (Rouche_Capelli(e) != ONE_RESULT) exit(1);
    e = feq_sys_rref(e); 
    setFVectorsPtr res = new TsetFVectors("");
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

/* risolve un sistema lineare */
setFVectorsPtr feq_sys_sol(FEqsys e){
    Trc type_res = Rouche_Capelli(e);
    if(type_res == NO_RESULT){
        return NULL;
    } else if(type_res == INF_RESULTS){
        return feq_sys_inf_sol(e);
    } else {
        return feq_sys_one_sol(e);
    }
}
