#include "all-headers.h"
#include <iostream>
using namespace std;

// Methods

/* contruttore de dafault della matrice fraction, imposta il numero di colonne e di righe a 0 */
Tfmatrix::Tfmatrix(){
    nr = nc = 0;
}

/* inizializza la matrice frazione con il numero di colonne e righe date */
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

/* inizializza la matrice frazione con il numero di colonne, di righe date e una striga per il nome */
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

/* inizializza la matricefrazione con il numero di colonne e di righe date con valori casuali compresi tra min e max */
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

/* distruttore */
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

/* inizializza una matrice chiedendo il numero di righe e il numero di colonne */
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

/* inizializza una matrice inserendo il numero di colonne e di righe direttamente come parametri */
FMatrix init_predefinition_fmatrix(string name, int r, int c){
    cout << "rows= " << r << endl;
    cout << "columns= " << c << endl;
    cout << endl;
    return insert_values_fmatrix(r, c, name);
}

/* prende in input il numero di righe, di colonne e il nome della matrice e permette di inserire i valori in forma float, fraction o int */
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

/* visualizza la matrice data approssimando i valori in float con precisione 2 */
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

void print_fmatrix_float_system(FMatrix m){
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

/* prende in input un puntatore a Tfmatrix e la visualizza sul prompt */
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

void print_fmatrix_system(FMatrix m){
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

/* prende in input una matrie m, l'identificatore intero di una colonna e un tipo char per determinare se studiare il denominatore o il numeratore, e restituisce il numero massimo di cifre usate in quella colonna della matrice dal numeratore o denominatore */
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

/* prende in input un puntatore a una matrice di float, la dimensione di una colonna e un'identificatore intero di una colonna, e restituisce il numero massino di caratteri usati degli elementi della matrice nella parte intera della colonna */
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

/* prende in input un puntatore a Tfmatrix e restituisce la sua matrice trasposta */
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

/* prende in input due matrici FMatrix e ne restituisce la somma */
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

/* prende in input due matrici FMatrix e ne restituisce la differenza */
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

/* prende in input due matrici e restituisce il loro prodotto se possibile */
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

/* prende in input un puntatore a Tfmatrix e un numero razionale che viene moltiplicato per ogni elemento della matrice */ 
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

/* prende in input un puntatore a Tfmatrix e due indici interi di due righe della matrice, e restituisce la matrice stessa con le righe scambiate */
void fraction_S(FMatrix m, int a, int b){
    FVector v = new Tfvector(m->mat[a], m->nc);
    m->mat[a] = m->mat[b]; m->mat[b] = v->array;
}

/* prende in input un puntatore a Tfmatrix, un indice intero di una riga della matrice e un puntatore a Tfraction, e restituisce la matrice stessa con la riga indicizza moltiplicata per la Tfraction puntata */
void fraction_D(FMatrix m, int a, Fraction lambda){
    int c = m->nc;
    for(int j = 0; j < c; j++)
        m->mat[a][j] = fraction_product(m->mat[a][j], lambda);
}

/* prendo in  input un puntatore a Tfmatrix, due indici interi di due righe della matrice e un puntatore a Tfraction, e restituisce la matrice stessa con la prima riga indicizzata sommata all'altra riga indicata dal secondo indice moltoplicata per la Tfraction puntata */
void fraction_E(FMatrix m, int d, int s, Fraction lambda){ 
    FVector v = new Tfvector(m->mat[s], m->nc);
    v->multiply(lambda);
    for(int j = 0; j < m->nc; j++) 
        m->mat[d][j] = fraction_sum(m->mat[d][j], v->array[j]);
}

/* prende in input un puntatore a Tfamtrix e la trasforma la matrice nella sua forma a scalini secondo l'algoritmo di gauss-jordan */
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

/* prende in input un punatore a Tfmatrix e restituisce la sue rref */
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

/* prende in input una matrice e restituisce un'altra matrice uguale a quella data */
FMatrix fraction_matrix_copy(FMatrix m){
    FMatrix r = new Tfmatrix(m->nr, m->nc);
    for(int i = 0; i < m->nr; i++){
        for(int j = 0; j < m->nc; j++){
            r->mat[i][j] = m->mat[i][j];
        }
    }
    return r;
}

/* prende in input una matrice e restituisce il suo rango */
int fraction_matrix_rank(FMatrix m){
    int counter = 0;
    FMatrix my_copy = fraction_matrix_gauss_jordan(m);
    for(int i = 0; i < my_copy->nr; ++i){
        for(int j = 0; j < my_copy->nc; ++j)
            if(my_copy->mat[i][j]->num != 0){ ++counter; j = my_copy->nc; }
    }
    return counter;
}

/* verifica che una le colonne di una matrice formino una base */
bool fraction_matrix_is_base(FMatrix m){
    return (m->nc == fraction_matrix_rank(m) && matrix_is_square(m));
}

/* verifica che una matrice sia quadrata */
bool matrix_is_square(FMatrix m){
    return (m->nc == m->nr);
}

/* prende in input una matrice e restituisce la sua inversa se possibile */
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

/* prende in input una matrice e un vettore ed esegue il prodotto se possibile */
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
