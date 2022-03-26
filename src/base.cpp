#include <iostream>
#include <cstdlib>
#include "all-headers.h"
using namespace std;

SNodeptr insertFirstS(SNodeptr n, Set b){
    return new Tbflist(b, n);
}

SNodeptr remove_ssearch(SNodeptr n){
    string name;
    cout << "Set name: ";
    fflush(stdin);
    cin >> name;
    if (n == NULL){
        return NULL;
    }
    SNodeptr t = n;
    if (n->b->name == name){
        t = t->next;
        delete n;
        return t;
    }
    while ((t->next != NULL) && (t->next->b->name != name)){
        t = t->next;
    }
    if (t->next != NULL){
        SNodeptr r = t->next;
        t->next = t->next->next;
        delete r;
        return n;
    }
    return n;
}

Set get_ssearch(SNodeptr n, string name){
    if (n == NULL){
        return NULL;
    }
    SNodeptr t = n;
    while (t != NULL){
        if (t->b->name == name){
            return t->b;
        }
        t = t->next;
    }
    return NULL;
}

bool isPresentS(SNodeptr n, string name){
    if (n == NULL){
        return false;
    }
    SNodeptr t = n;
    while (t != NULL){
        if (t->b->name == name){
            return true;
        }
        t = t->next;
    }
    return false;
}

SNodeptr insertS(SNodeptr n, string name){
    if (!isPresentS(n, name)){
        return insertFirstS(n, init_set_fvectors(name));
    }
    else{
        cout << "Set with the same name already present" << endl
             << endl;
    }
    return n;
}

void command_print_vectors_set(SNodeptr n){
    string userinput;
    cout << "Set name: ";
    fflush(stdin);
    cin >> userinput;
    Set b = get_ssearch(n, userinput);
    if (b != NULL){
        cout << endl;
        b->print();
        cout << endl
             << endl;
    }
    else{
        cout << "Set not found" << endl
             << endl;
    }
}

void command_print_all_sets(SNodeptr n){
    if (n == NULL){
        cout << "No saved sets" << endl
             << endl;
    }
    SNodeptr t = n;
    while (t != NULL){
        print_set_fvectors(t->b);
        cout << endl
             << endl;
        t = t->next;
    }
}

SNodeptr command_new_vectors_set(SNodeptr n){
    string name;
    cout << "Set name: ";
    fflush(stdin);
    cin >> name;
    return insertS(n, name);
}

void command_set_is_base(SNodeptr n){
    string name;
    cout << "Set name: ";
    fflush(stdin);
    cin >> name;
    Set a = get_ssearch(n, name);
    if (a != NULL){
        if (set_fvectors_is_base(a)){
            cout << "The set is a base of R" << a->n_th << endl
                 << endl;
        } else{
            cout << "The set is not a base" << endl
                 << endl;
        }
    } else {
        cout << "Set not found" << endl
             << endl;
    }
}

void command_set_is_independent(SNodeptr n){
    string name;
    cout << "Set name: ";
    fflush(stdin);
    cin >> name;
    Set a = get_ssearch(n, name);
    if (a != NULL){
        if (set_fvectors_is_linearly_independent(a)){
            cout << "The set is l.independent" << endl
                 << endl;
        } else {
            cout << "The set is not l.independent" << endl
                 << endl;
        }
    } else {
        cout << "Set not found" << endl
             << endl;
    }
}

void command_set_is_generator(SNodeptr n){
    string name;
    cout << "Set name: ";
    fflush(stdin);
    cin >> name;
    Set a = get_ssearch(n, name);
    if (a != NULL){
        if (set_fvectors_is_linearly_independent(a)){
            cout << "The set is generator of R" << a->n_th << endl
                 << endl;
        } else {
            cout << "The set is not a generator of R" << a->n_th << endl
                 << endl;
        }
    } else {
        cout << "Set not found" << endl
             << endl;
    }
}

SNodeptr command_gram_schmidt(SNodeptr n){
    string name;
    cout << "Set name: ";
    fflush(stdin);
    cin >> name;
    Set a = get_ssearch(n, name);
    if (a != NULL){
        Set b = Gram_Schmidt(a);
        b->name = a->name + "gs";
        print_set_fvectors(b);
        return insertFirstS(n, b);
    } else {
        cout << "Set not found" << endl
             << endl;
    }
    return n;
}

SNodeptr command_orthogonal_complement(SNodeptr n){
    string name;
    cout << "Set name: ";
    fflush(stdin);
    cin >> name;
    Set a = get_ssearch(n, name);
    if (a != NULL){
        Set b = orthogonal_complement(a);
        b->name = a->name + "ort";
        print_set_fvectors(b);
        return insertFirstS(n, b);
    } else {
        cout << "Set not found" << endl
             << endl;
    }
    return n;
}

SNodeptr command_base_completion(SNodeptr n){
    string name;
    cout << "Set name: ";
    fflush(stdin);
    cin >> name;
    Set a = get_ssearch(n, name);
    if (a != NULL){
        Set b = completion_of_base(a);
        if (b != NULL){
            b->name = a->name + "_C";
            print_set_fvectors(b);
            return insertFirstS(n, b);
        } else {
            return n;
        }
    } else {
        cout << "Set not found" << endl
             << endl;
    }
    return n;
}

Matrix base_change(Set b1, Set b2){
    Matrix m1 = set_vectors_to_fmatrix(b1), m2 = set_vectors_to_fmatrix(b2);
    if (fraction_matrix_is_base(m1) && fraction_matrix_is_base(m2) && (m1->nc == m2->nc)){
        Matrix full = new Tfmatrix(m1->nr, (m1->nc + m2->nc));
        int r = m1->nr, c1 = m1->nc, c2 = m2->nc, tot = c1 + c2;
        for (int i = 0; i < r; i++){
            for (int j = 0; j < tot; j++){
                if (j < c1){
                    full->mat[i][j]->num = m2->mat[i][j]->num;
                    full->mat[i][j]->den = m2->mat[i][j]->den;
                } else {
                    full->mat[i][j]->num = m1->mat[i][j - c1]->num;
                    full->mat[i][j]->den = m1->mat[i][j - c1]->den;
                }
            }
        }
        Matrix rref = fraction_matrix_rref(full);
        Matrix res = new Tfmatrix(r, c1);
        for (int i = 0; i < r; i++){
            for (int j = c1; j < tot; j++){
                res->mat[i][j - c1] = rref->mat[i][j];
            }
            cout << endl;
        }
        return res;
    } else {
        cout << "The sets need to be a base of the same vectorial space" << endl
             << endl;
    }
    return NULL;
}