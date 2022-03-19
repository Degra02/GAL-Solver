#include "all-headers.h"
#include <iostream>
using namespace std;

// Methods

/* default matrix constructor */
Tfmatrix::Tfmatrix(){
    nr = nc = 0;
}

/* rows and columns constructor */
Tfmatrix::Tfmatrix(int _nr, int _nc){
    nr = _nr; nc = _nc;
    mat = new Fraction*[nr];
    for(int i = 0; i < nr; i++){
        mat[i] = new Fraction[nc];
        for(int j = 0; j < nc; j++){
            mat[i][j] = new Tfraction();
        }
    }
}

/* name, rows and columns constructor */
Tfmatrix::Tfmatrix(string _name, int _nr, int _nc) {
    nr = _nr; nc = _nc; name = _name;
    mat = new Fraction*[nr];
    for(int i = 0; i < nr; i++){
        mat[i] = new Fraction[nc];
        for(int j = 0; j < nc; j++){
            mat[i][j] = new Tfraction();
        }
    }
}

/* random values matrix init (used for testing) */
Tfmatrix::Tfmatrix(int _nr, int _nc, int min, int max){
    nr = _nr; nc = _nc;
    mat = new Fraction*[nr];
    for(int i = 0; i < nr; i++){
        mat[i] = new Fraction[nc];
        for(int j = 0; j < nc; j++){
            mat[i][j] = 
                fraction_simplification(new Tfraction(rand() % (max - min + 1) + min, 1));
        }
    }
}

/* destructor */
Tfmatrix::~Tfmatrix(){
    for(int i = 0; i < nr; i++){
        for(int j = 0; j < nc; j++){
            delete mat[i][j];
        }
        delete[] mat[i];
    }
    delete[] mat;
}

// Functions

/* initializes the matrix asking rows and columns */
FMatrix init_fmatrix(string name){
    int r, c;
	cout << "rows= "; fflush(stdin); cin >> r;
	cout << "columns= "; fflush(stdin); cin >> c;
    cout << endl;
    return insert_values_fmatrix(r, c, name);
}

FMatrix init_fmatrix_known_dim(string name, int r, int c){
    return insert_values_fmatrix(r, c, name);
}

/* initializes matrix with predefined n° of rows and columns */
FMatrix init_predefinition_fmatrix(string name, int r, int c){
    cout << "rows= " << r << endl;
    cout << "columns= " << c << endl;
    cout << endl;
    return insert_values_fmatrix(r, c, name);
}

/* lets the user insert int, float or fraction values inside a matrix */
FMatrix insert_values_fmatrix(int r, int c, string name){
    FMatrix m = new Tfmatrix(name, r, c); Fraction f; string value; 
    for(int i = 0; i < r; i++){ 
        cout << "   "; 
        for(int j = 0; j < c; j++){ 
            cin >> value; f = str_to_fraction(value);
            m->mat[i][j] = fraction_simplification(f); 
        }
    } 
    fflush(stdin); cout << endl;
    return m;
}

/* float print of the given matrix, with 2 decimal digits */
void print_fmatrix_float(FMatrix m){
    int r = m->nr; int c = m->nc; 
    int figures[c];
    float** f = new float*[r];
    for(int i = 0; i < r; ++i) f[i] = new float[c];
    cout << "Name: " << "\x1b[38;5;50m" << m->name << "\x1b[0m";
    cout << endl << endl;
    for(int j = 0; j < c; ++j){
        for(int i = 0; i < r; ++i){
            f[i][j] = 
                roundf(((float)m->mat[i][j]->num / m->mat[i][j]->den)*100.0)/100.0;
        }
        figures[j] = float_find_max_figures_column(f, r, j);
    }
    for(int i = 0; i < r; ++i){
        cout << "   ";
        for(int j = 0; j < c; ++j){
            print_format_float(f[i][j], figures[j]);
        }
        printf("\n");
    }
    cout << endl;
}

void print_fmatrix_float_system(FMatrix m){ // support function for linear equations systems
    int r = m->nr; int c = m->nc; 
    int figures[c];
    float** f = new float*[r];
    for(int i = 0; i < r; ++i) f[i] = new float[c];
    cout << "Name: " << "\x1b[38;5;50m" << m->name << "\x1b[0m";
    cout << endl << endl;
    for(int j = 0; j < c; ++j){
        for(int i = 0; i < r; ++i){
            f[i][j] = 
                roundf(((float)m->mat[i][j]->num / m->mat[i][j]->den)*100.0)/100.0;
        }
        figures[j] = float_find_max_figures_column(f, r, j);
    }
    for(int i = 0; i < r; ++i){
        cout << "   ";
        for(int j = 0; j < c; ++j){
            if(j == c-1){
                printf("%c", 179);
                print_format_float(f[i][j], figures[j]);
            } else {
                print_format_float(f[i][j], figures[j]);
            }
        }
        printf("\n");
    }
    cout << endl;
}

/* prints the given Matrix */
void print_fmatrix(FMatrix m){
    int r = m->nr; int c = m->nc;
    int figures_num[c];
    int figures_den[c];
    cout << "Name: " << "\x1b[38;5;50m" << m->name << "\x1b[0m";
    cout << endl << endl;
    for(int j = 0; j < c; ++j){
        figures_num[j] = fraction_find_max_figures_column(m, j, 'n');
        figures_den[j] = fraction_find_max_figures_column(m, j, 'd');
    }
    for(int i = 0; i < r; ++i){
        cout << "   "; 
        for(int j = 0; j < c; ++j){
            print_format_fraction(m->mat[i][j], figures_num[j], figures_den[j]);
        }
        printf("\n");
    }
    cout << endl;
}

void print_fmatrix_system(FMatrix m){ // support function for printing linear equations systems
    int r = m->nr; int c = m->nc;
    int figures_num[c];
    int figures_den[c];
    cout << "Name: " << "\x1b[38;5;50m" << m->name << "\x1b[0m";
    cout << endl << endl;
    for(int j = 0; j < c; ++j){
        figures_num[j] = fraction_find_max_figures_column(m, j, 'n');
        figures_den[j] = fraction_find_max_figures_column(m, j, 'd');
    }
    for(int i = 0; i < r; ++i){
        cout << "   "; 
        for(int j = 0; j < c; ++j){
            if(j == c-1){
                printf("%c", 179);
                print_format_fraction(m->mat[i][j], figures_num[j], figures_den[j]);
            } else {
                print_format_fraction(m->mat[i][j], figures_num[j], figures_den[j]);
            }
        }
        printf("\n");
    }
    cout << endl;
}

/* takes a matrix, the column number 
and a char that tells the function to check the numerator or the denominator, 
and returns the maximum number of spaces used to print that fraction */
int fraction_find_max_figures_column(FMatrix m, int column, char type){
    int max_c = 0, n, space;
    bool control = (type == 'n');
    int r = m->nr;
    for(int i = 0; i < r; ++i){
        if(m->mat[i][column]->den != 1){
             n = (control ? m->mat[i][column]->num : m->mat[i][column]->den);
        } else {
            n = m->mat[i][column]->num;
        } 
        space = figures(abs(n));
        if(m->mat[i][column]->den == 1) 
            space = (control ? (space / 2) : (space - 1) / 2);
        if(n < 0) ++space;
        if(space > max_c) max_c = space;
    }
    return max_c;
}

/* takes a float matrix pointer and the number of the column and returns 
the maximum nuber of spaces used for that column */
int float_find_max_figures_column(float** f, int dim, int column){
    int max_c = figures(abs(f[0][column])), space;
    if(f[0][column] < 0.0) ++max_c; 
    for(int i = 1; i < dim; ++i){
        space = figures(abs(f[i][column])); 
        if(f[i][column] < 0.0) ++space;
        if(space > max_c) max_c = space;
    }
    return max_c;
}

/* returns a new matrix, transpose of the given matrix */
FMatrix fraction_matrix_transpose(FMatrix m){
    FMatrix mT = new Tfmatrix(m->nc, m->nr);
    int r = m->nr, c = m->nc;
    for(int i = 0; i < r; i++){
        for(int j = 0; j < c; j++){
            mT->mat[j][i] = m->mat[i][j];
        }
    }
    return mT;
}

/* sum of two matrices */
FMatrix fraction_matrix_sum(FMatrix a, FMatrix b){
    if(a->nr != b->nr || a->nc != b->nc) return new Tfmatrix();
    int r = a->nr, c = a->nc;
    FMatrix sum = new Tfmatrix(r, c);
    for(int i = 0; i < r; i++){
        for(int j = 0; j < c; j++){
            sum->mat[i][j] = fraction_sum(a->mat[i][j], b->mat[i][j]);
        }
    }
    return sum;
}

/* difference of two matrices */
FMatrix fraction_matrix_difference(FMatrix a, FMatrix b){
    if(a->nr != b->nr || a->nc != b->nc) return new Tfmatrix();
    int r = a->nr, c = a->nc;
    FMatrix sum = new Tfmatrix(r, c);
    for(int i = 0; i < r; i++){
        for(int j = 0; j < c; j++){
            sum->mat[i][j] = fraction_difference(a->mat[i][j], b->mat[i][j]);
        }
    }
    return sum;
}

/* product (if possible) of two matrices */
FMatrix fraction_matrix_multiplication(FMatrix a, FMatrix b){
    if(a->nc == b->nr){
        FMatrix multi = new Tfmatrix(a->nr, b->nc);
        int r = multi->nr, c = multi->nc;
        for(int i = 0; i < r; i++){
            for(int j = 0; j < c; j++){
                for(int k = 0; k < c; k++){
                    multi->mat[i][j] = 
                        fraction_sum(multi->mat[i][j], fraction_product(a->mat[i][k], b->mat[k][j]));
                }
            }
        }
        return multi;
    } else {
        cout << "Impossible to multiply the given functions" << endl << endl;
        return NULL;
    }
}

/* scalar product of the given matrix */ 
FMatrix fraction_matrix_scalar_multiplication(FMatrix a, float lambda){
    Fraction l = new Tfraction(lambda);
    FMatrix res = new Tfmatrix(a->nr, a->nc);
    int r = a->nr, c = a->nc;
    for (int i = 0; i < r; i++){
        for (int j = 0; j < c; j++){
            res->mat[i][j] = fraction_product(l, a->mat[i][j]);
        }
    }
    return res;
}

/* S opeartion for Gauss Jordan algorithm */
void fraction_S(FMatrix m, int a, int b){
    FVector v = new Tfvector(m->mat[a], m->nc);
    m->mat[a] = m->mat[b]; m->mat[b] = v->array;
}

/* D opeartion for Gauss Jordan algorithm */
void fraction_D(FMatrix m, int a, Fraction lambda){
    int c = m->nc;
    for(int j = 0; j < c; j++)
        m->mat[a][j] = fraction_product(m->mat[a][j], lambda);
}

/* E operation for Gauss Jordan algorithm */
void fraction_E(FMatrix m, int d, int s, Fraction lambda){ 
    FVector v = new Tfvector(m->mat[s], m->nc);
    v->multiply(lambda);
    for(int j = 0; j < m->nc; j++) 
        m->mat[d][j] = fraction_sum(m->mat[d][j], v->array[j]);
}

/* Gauss Jordan algorithm to turn the given matrix into its stairs form */
FMatrix fraction_matrix_gauss_jordan(FMatrix m){
    FMatrix mg = fraction_matrix_copy(m); 
    Fraction lambda; int zero_column = 0;
    int rm = mg->nr, c = mg->nc;
    for(int j = 0; j < c; ++j){
        int i = (j - zero_column);
        while(i < rm && mg->mat[i][j]->num == 0) ++i;
        if(i == rm){
            ++zero_column;
            continue; // passa alla prossima colonna 
        }
        if(i != (j - zero_column)) fraction_S(mg, i, (j - zero_column)); 
        i = (j - zero_column);
        for(int r = i + 1; r < rm; ++r){
            if(mg->mat[r][j]->num != 0){
                lambda = fraction_quotient(
                    fraction_product(new Tfraction(-1, 1), mg->mat[r][j]),
                    mg->mat[i][j]
                );
                fraction_E(mg, r, i, lambda);
            }
        }
    }
    return mg;
}

/* algorithm to calculate the rref of the given matrix */
FMatrix fraction_matrix_rref(FMatrix m){
    FMatrix mrr = fraction_matrix_gauss_jordan(m); 
    Fraction lambda; int no_pivot_column = 0, i; 
    for (int j = 0; j < mrr->nc; ++j){
        i = (j - no_pivot_column);
        if(i == mrr->nr) break; // termina la rref
        if(mrr->mat[i][j]->num == 0){
            ++no_pivot_column;
            continue; // passa alla prossima colonna 
        }
        if(mrr->mat[i][j]->num != 0){
            lambda = fraction_quotient(new Tfraction(1, 1), mrr->mat[i][j]);
            fraction_D(mrr, i, lambda);
        }
        for(int r = i - 1; r >= 0; --r){
            if(mrr->mat[r][j]->num != 0){
                lambda = fraction_product(new Tfraction(-1, 1), mrr->mat[r][j]);
                fraction_E(mrr, r, i, lambda);
            }
        }
    }
    return mrr;
}

/* copies a matrix into a new one */
FMatrix fraction_matrix_copy(FMatrix m){
    FMatrix r = new Tfmatrix(m->nr, m->nc);
    for(int i = 0; i < m->nr; i++){
        for(int j = 0; j < m->nc; j++){
            r->mat[i][j] = m->mat[i][j];
        }
    }
    return r;
}

/* returns the rank of the given matrix */
int fraction_matrix_rank(FMatrix m){
    int counter = 0;
    FMatrix my_copy = fraction_matrix_gauss_jordan(m);
    for(int i = 0; i < my_copy->nr; ++i){
        for(int j = 0; j < my_copy->nc; ++j)
            if(my_copy->mat[i][j]->num != 0){ ++counter; j = my_copy->nc; }
    }
    return counter;
}

/* checks if the columns of the given matrix form a base */
bool fraction_matrix_is_base(FMatrix m){
    return (m->nc == fraction_matrix_rank(m) && matrix_is_square(m));
}

/* checks if the matrix is squared */
bool matrix_is_square(FMatrix m){
    return (m->nc == m->nr);
}

/* takes a matrix and returns the reverse matrix (if possible) */
FMatrix fraction_matrix_reverse(FMatrix m){
    int r = m->nr, c = m->nc;
    if((!matrix_is_square(m)) || (fraction_matrix_rank(m) != c)){
        cout << "Reverse matrix does not exit." << endl << endl;
        return NULL;
    }
    FMatrix mr = new Tfmatrix(r, c);
    FMatrix mI = new Tfmatrix(r, 2 * c);
    for(int i = 0; i < r; ++i){
        for(int j = 0; j < c; ++j) mI->mat[i][j] = m->mat[i][j];
        for(int j = c; j < 2 * c; ++j){
            if(i == j - 3) mI->mat[i][j] = new Tfraction(1, 1);
            else mI->mat[i][j] = new Tfraction(0, 1);
        }
    }
    mI = fraction_matrix_rref(mI);
    for(int i = 0; i < r; ++i){
        for(int j = 0; j < c; ++j){
            mr->mat[i][j] = mI->mat[i][j + 3];
        }
    }
    return mr;
}

/* product between matrix and vector (if possible) */
FVector fraction_matrix_fvector_product(FMatrix m, FVector v){
    int r = m->nr, c = m->nc;
    if(v->n == c){
        FVector vm = new Tfvector(r); //dim = m->nr
        for(int i = 0; i < vm->n; i++){
            vm->array[i] = str_to_fraction("0");
        }
        for(int i = 0; i < r; ++i){
            for(int j = 0; j < c; ++j){
                vm->array[i] = fraction_sum(vm->array[i], (fraction_product(v->array[j], m->mat[i][j])));
            }
        }
        return vm;
    }
    return NULL;
}

PivotRowsColumnsPtr pivot_rows_columns(FMatrix m){ 
    int rank = fraction_matrix_rank(m);
    PivotRowsColumnsPtr info = new TpivotRowsColmuns(rank);
    int num_columns = m->nc;
    int i = 0, j = 0, free_column = 0;
    while(j < num_columns && i < m->nr){
        i = j - free_column;
        if(i == m->nr);
        else if(m->mat[i][j]->num == 0){
            ++free_column;
        } else {
            info->pivot_columns[i] = j;
            info->pivot_rows[i] = i; 
        }
        ++j;
    }
    return info;
}

FreeColumnsPtr free_columns(FMatrix m){
    int rank = fraction_matrix_rank(m); 
    int num_columns = m->nc; 
    FreeColumnsPtr info = new TfreeColumns(num_columns - rank);
    int i = 0, j = 0, free_columns = 0, counter = 0;
    while(j < num_columns){
        i = j - free_columns;
        if(i >= m->nr){
            info->free_columns[counter] = j;
            ++counter;
        } else if(m->mat[i][j]->num == 0){
            info->free_columns[counter] = j;
            ++counter;
            ++free_columns;
        }
        ++j;
    }
    return info;
}
