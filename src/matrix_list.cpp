#include <iostream>
#include <cstdlib>
#include "all-headers.h"
using namespace std;

MNodeptr insertFirst(MNodeptr n, Matrix m){
    return new TMnode(m, n);
}

MNodeptr remove_search(MNodeptr n){
    string name; 
    cout << "Matrix name= "; fflush(stdin); cin >> name;
    if(n == NULL){
        return NULL;
    }
    MNodeptr t = n;
    if(n->m->name == name){
        t = n->next;
        delete n;
        return t;
    }
    while((t->next != NULL) && (t->next->m->name != name)){
        t = t->next;
    }
    if(t->next != NULL){
        MNodeptr r = t->next;
        t->next = t->next->next;
        delete r;
        return n;
    }
    return n;
}

Matrix get(MNodeptr n){
    return n->m;
}

Matrix get_search (MNodeptr n, string name){ // returns the matrix with the given name, NULL otherwise
    if(n == NULL){
        return NULL;
    }
    MNodeptr t = n;
    while((t != NULL) && (t->m->name != name)){
        t = t->next;
    }
    if(t == NULL){
        return NULL;
    } else {
        return t->m;
    }  

}

bool isPresent(MNodeptr n, string name){
    if(n == NULL){
        return false;
    }
    MNodeptr t = n;
    while((t != NULL)){
        if(t->m->name == name){
            return true;
        }
        t = t->next;
    }
    return false;
}

MNodeptr insertM(MNodeptr n, string name){
    if(! isPresent(n, name)){
        n = insertFirst(n, init_fmatrix(name));
    } else {
        cout << "Matrix with the same name already saved" << endl << endl;
    }
    return n;
}

void command_print_matrix(MNodeptr n){
    string userinput;
    cout << "Matrix name: "; fflush(stdin); cin >> userinput;
    Matrix m = get_search(n, userinput);
    string choice;
    cout << "Print format: "; fflush(stdin); cin >> choice;

    if(m != NULL){
        if(choice  == "fraction"){
            print_fmatrix(m);
        } else if(choice == "float"){
            print_fmatrix_float(m);
        } else {
            cout << endl << "Invalid print format" << endl << endl;
        }
    } else {
        cout << endl << "Matrix not found" << endl << endl;
    }
}

void command_print_all_matrices(MNodeptr n){
    if(n == NULL){
        cout << "No saved matrices" << endl << endl;
    }
    MNodeptr t = n;
    while(t != NULL){
        print_fmatrix(t->m); cout << endl << endl;
        t = t->next;
    }
}

MNodeptr command_new_matrix(MNodeptr n){
    string name;
    cout << "Name= "; fflush(stdin); cin >> name;
    return insertM(n, name);
}

MNodeptr command_matrix_product(MNodeptr n){
    string n1, n2;
    cout << "Matrix names: "; fflush(stdin); cin >> n1 >> n2;
    Matrix m1, m2, res;
    m1 = get_search(n, n1); m2 = get_search(n, n2);
    if((m1 != NULL) && (m2 != NULL)){
        res = fraction_matrix_multiplication(m1, m2);
        if(res != NULL){
            res->name = m1->name + "x" + m2->name;
            print_fmatrix(res);
            return insertFirst(n, res);
        }
    } else if(m1 == NULL){
        cout << "No such matrix with name " << n1 << endl << endl;
    } else if(m2 == NULL){
        cout << "No such matrix with name " << n2 << endl << endl;
    } else {
        cout << "No such matrixes" << endl << endl;
    }
    return n;
}

MNodeptr command_matrix_sum(MNodeptr n){
    string n1, n2;
    cout << "Matrix names: "; fflush(stdin); cin >> n1 >> n2;
    Matrix m1, m2, res;
    m1 = get_search(n, n1); m2 = get_search(n, n2);
    if(m1 != NULL && m2 != NULL){
        res = fraction_matrix_sum(m1, m2);
        res->name = m1->name + "+" + m2->name;
    } else if(m1 == NULL){
        cout << "No such matrix with name " << n1 << endl << endl;
    } else if(m2 == NULL){
        cout << "No such matrix with name " << n2 << endl << endl;
    } else {
        cout << "No such matrixes" << endl << endl;
    }
    print_fmatrix(res);
    return insertFirst(n, res);
}

MNodeptr command_matrix_difference(MNodeptr n){
    string n1, n2;
    cout << "Matrix names: "; fflush(stdin); cin >> n1 >> n2;
    Matrix m1, m2, res;
    m1 = get_search(n, n1); m2 = get_search(n, n2);
    if(m1 != NULL && m2 != NULL){
        res = fraction_matrix_difference(m1, m2);
        res->name = m1->name + "-" + m2->name;
    } else if(m1 == NULL){
        cout << "No such matrix with name " << n1 << endl << endl;
    } else if(m2 == NULL){
        cout << "No such matrix with name " << n2 << endl << endl;
    } else {
        cout << "No such matrixes" << endl << endl;
    }
    print_fmatrix(res);
    return insertFirst(n, res);
}

MNodeptr command_matrix_traspose(MNodeptr n){
    string name;
    cout << "Matrix name: "; fflush(stdin); cin >> name;
    Matrix m1 = get_search(n, name);
    Matrix t;
    if(m1 != NULL){
        t = fraction_matrix_transpose(m1);
        t->name = m1->name + "T";
    } else {
        cout << "No such matrix" << endl << endl;
    }
    print_fmatrix(t);
    return insertFirst(n, t);
}

MNodeptr command_matrix_stairs(MNodeptr n){
    string name;
    cout << "Matrix name: "; fflush(stdin); cin >> name;
    Matrix m1 = get_search(n, name); Matrix s;
    if(m1 != NULL){
        s = fraction_matrix_gauss_jordan(m1);
        s->name = m1->name + "sf"; // means stairs form
    } else {
        cout << "No such matrix" << endl << endl;
    }
    print_fmatrix(s);
    return insertFirst(n, s);
}

MNodeptr command_matrix_scalar_mult(MNodeptr n){
    string name; float lambda;
    cout << "Matrix name: "; fflush(stdin); cin >> name;
    cout << "Lambda= "; cin >> lambda;
    Matrix m1 = get_search(n, name); Matrix t;
    if(m1 != NULL){
        t = fraction_matrix_scalar_multiplication(m1, lambda);
        Fraction a = fraction_simplification(str_to_fraction(to_string(lambda)));
        if(a->den == 1){
            t->name = to_string(a->num) + m1->name;
        } else {
            t->name = to_string(a->num) + "/" + to_string(a->den) + m1->name;
        }
    } else {
        cout << "No such matrix" << endl << endl;
    }
    print_fmatrix(t);
    return insertFirst(n, t);
}

MNodeptr command_matrix_rref(MNodeptr n){
    string name;
    cout << "Matrix name: "; fflush(stdin); cin >> name;
    Matrix m = get_search(n, name); Matrix r;
    if(m != NULL){
        r = fraction_matrix_rref(m);
        r->name = m->name + "rf"; // means row reduced echelon form
    } else {
        cout << "No such matrix" << endl << endl;
    }
    print_fmatrix(r);
    return insertFirst(n, r);
}

void command_matrix_rank(MNodeptr n){
    string name;
    cout << "Matrix name: "; fflush(stdin); cin >> name;
    Matrix m = get_search(n, name);
    if(m != NULL){
        cout << "Rank= " << fraction_matrix_rank(m);
        cout << endl << endl;
    } else {
        cout << "No such matrix" << endl << endl;
    }
    
}

void command_matrix_is_base(MNodeptr n){
    string name; cout << "Matrix name: "; fflush(stdin); cin >> name;
    Matrix m = get_search(n, name);
    if(m != NULL){ 
        if(fraction_matrix_is_base(m)){
            printf("The columns are a base of R%d\n\n", fraction_matrix_rank(m)); 
            cout << endl << endl;
        } else {
            cout << "The matrix is not a base" << endl << endl;
        }
    } else {
        cout << "No such matrix" << endl << endl;
    }
}

void command_matrix_det(MNodeptr n){
    string name; cout << "Matrix name: "; fflush(stdin); cin >> name;
    Matrix m = get_search(n, name);
    if(m != NULL){
        Fraction a = det(m);
        if(a != NULL){
            cout << "Det= "; a->print();
            cout << "  ~  "; a->print_float();
            cout << endl << endl;
        }
    } else {
        cout << "Matrix not found" << endl << endl;
    }
}

MNodeptr command_matrix_reverse(MNodeptr n){
    string name; cout << "Matrix name: "; fflush(stdin); cin >> name;
    Matrix m = get_search(n, name);
    if(m != NULL){
        Matrix m1 = fraction_matrix_reverse(m);
        if(m1 != NULL){
            m1->name = m->name + "-1";
            print_fmatrix(m1);
            return insertFirst(n, m1);
        } else {
            return n;
        }
    } else {
        cout << "Matrix not found" << endl << endl;
    }
    return n;
}
