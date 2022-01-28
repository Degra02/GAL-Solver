#include <iostream>
#include <ctime>
#include <bits/stdc++.h>
#include "all-headers.h"
using namespace std;

Lists command_system_build(Lists list){
    string mn; cout << "Matrix name: "; fflush(stdin); cin >> mn;
    FMatrix a = get_search(list->Mlist, mn);
    if(a == NULL){
        cout << "No such matrix" << endl << endl;
        return list;
    }
    string vn; cout << "Vector name: "; fflush(stdin); cin >> vn;
    FVector b = get_vsearch(list->Vlist, vn);
    if(b == NULL){
        cout << "No such vector" << endl << endl;
        return list;
    }
    if(b->n != a->nr){
        cout << "Invalid vector (wrong size)" << endl << endl;
        return list;
    }
    FMatrix c = fraction_matrix_copy(a);
    FVector d = fraction_vector_copy(b);
    FEqsys sys = new Tfeqsys(c, d);
    sys->name = a->name + b->name; 
    cout << "System name:" << "\x1b[38;5;50m" << sys->name << "\x1b[0m" << endl << endl;
    list->Eqlist = insertFirstE(list->Eqlist, sys);
    return list;
}

Lists command_save_function(Lists list){
    Function f =list->Flist->f;
    if(f != NULL){
        list->Mlist = insertFirst(list->Mlist, f->mr);
        list->Slist = insertFirstS(list->Slist, f->b1);
        list->Slist = insertFirstS(list->Slist, f->b2);
    }
    return list;
}

Lists command_apply_function(Lists list){
    string n1, n2, choice; cout << "Function name: "; fflush(stdin); cin >> n1;
    Function f = get_fsearch(list->Flist, n1);
    if(f != NULL){
        printf("\x01b[1;38;5;3mExisting\x01b[0m vector or \x01b[1;38;5;3mnew\x01b[0m: ");
        fflush(stdin); cin >> choice;
        if(choice == "existing"){
            cout << "Vector name: "; fflush(stdin); cin >> n2;
            FVector v = get_vsearch(list->Vlist, n2);
            if(v != NULL){
                FVector v2 = apply_linear_function(f, v);
                if(v2 != NULL){
                    v2->name = f->name + "(" + v->name + ")";
                    print_fvector(v2);
                    list->Vlist = insertFirstV(list->Vlist, v2);
                    return list;
                } else {
                    cout << "The vector does not belong to the domain of the function" << endl << endl;
                    return list;
                }
            } else {
                cout << "Vector not found" << endl << endl; return list;
            }
        } else if(choice == "new"){
            FVector v2 = new Tfvector(f->mr->nc); string value;
            cout << "Vector name: "; fflush(stdin); cin >> n2; cout << "    "; v2->name = n2;
            for(int i = 0; i < v2->n; ++i){
                cin >> value;
                v2->array[i] = fraction_simplification(str_to_fraction(value));
            }
            list->Vlist = insertFirstV(list->Vlist, v2);
            FVector vf = apply_linear_function(f, v2); vf->name = f->name + "(" + v2->name + ")";
            print_fvector(vf); list->Vlist = insertFirstV(list->Vlist, vf);
            return list;
        } else {
            cout << "Invalid choice" << endl << endl; return list;
        }
    } else {
        cout << "Function not found" << endl << endl;
    }
    return list;
}

Lists command_function_ker(Lists list){
    string name; cout << "Function name: "; fflush(stdin); cin >> name;
    Function f = get_fsearch(list->Flist, name);
    if(f != NULL){
        setFVectorsPtr k = Ker(f); k->name = "ker(" + f->name + ")";
        print_set_fvectors(k);
        list->Slist = insertFirstS(list->Slist, k); return list;
    } else {
        cout << "Function not found: " << endl << endl;
    }
    return list;
}

Lists command_function_im(Lists list){
    string name; cout << "Function name: "; fflush(stdin); cin >> name;
    Function f = get_fsearch(list->Flist, name);
    if(f != NULL){
        setFVectorsPtr i = Im(f); i->name = "Im(" + f->name + ")";
        print_set_fvectors(i);
        list->Slist = insertFirstS(list->Slist, i); return list;
    } else {
        cout << "Function not found: " << endl << endl;
    }
    return list;
}

Lists command_counter_image(Lists list){
    string name; cout << "Function name: "; fflush(stdin); cin >> name;
    Function f = get_fsearch(list->Flist, name);
    if(f != NULL){
        string vname; cout << "Vector name: "; fflush(stdin); cin >> vname;
        if(isPresentV(list->Vlist, vname)){
            FVector v = get_vsearch(list->Vlist, vname);
            setFVectorsPtr cim = Counter_Im(f, v);
            cim->name = v->name + "cim"; // stands for counter image
            list->Slist = insertFirstS(list->Slist, cim);
            print_set_fvectors(cim); cout << endl;
        } else {
            FVector v = init_fvector(name);
            setFVectorsPtr cim = Counter_Im(f, v);
            cim->name = v->name + "cim";
            list->Slist = insertFirstS(list->Slist, cim);
            print_set_fvectors(cim); cout << endl;
        }
        return list;
    } else {
        cout << "Function not found: " << endl << endl;
    }
    return list;
}

Function init_function_from_saved(string name, Lists l){
    string n1, n2, n3;
    cout << "From base: "; fflush(stdin); cin >> n1;
    cout << "To base: "; fflush(stdin); cin >> n2;
    setFVectorsPtr b1 = get_ssearch(l->Slist, n1), b2 = get_ssearch(l->Slist, n2);
    if((b1 == NULL) || (b2 == NULL)){
        cout << "Base not found" << endl << endl; return NULL;
    }
    cout << "Representative matrix name: "; fflush(stdin); cin >> n3;
    FMatrix m1 = get_search(l->Mlist, n3);
    if(m1 != NULL){
        FMatrix m2 = fraction_matrix_copy(m1);
        m2->name = "M" + b1->name + b2->name + "( " + name + " )";
        return new Tfunction(name, b1, b2, m2);
    } else {
        cout << "Matrix not found" << endl << endl; return NULL;
    }
}

Lists command_new_function(Lists list){
    string name; cout << "Function name: "; fflush(stdin); cin >> name;
    if(! isPresentF(list->Flist, name)){
        string n1, n2, n3; cout << "Base \"from\": "; fflush(stdin); cin >> n1;
        setFVectorsPtr b1, b2; FMatrix m;
        if(isPresentS(list->Slist, n1)){
            b1 = get_ssearch(list->Slist, n1);
        } else {
            b1 = init_set_fvectors(n1);
            list->Slist = insertFirstS(list->Slist, b1);
        }
        cout << "Base \"to\": "; fflush(stdin); cin >> n2;
        if(isPresentS(list->Slist, n2)){
            b2 = get_ssearch(list->Slist, n2);
        } else {
            b2 = init_set_fvectors(n2);
            list->Slist = insertFirstS(list->Slist, b2);
        }
        string choice; cout << "Function in \x01b[1;38;5;3mexpression\x01b[0m form or \x01b[1;38;5;3mmatrix\x01b[0m?: ";
        fflush(stdin); cin >> choice;
        if(choice == "matrix"){
            cout << "Representative matrix name: "; fflush(stdin); cin >> n3;
            if(isPresent(list->Mlist, n3)){
                m = get_search(list->Mlist, n3);
            } else {
                m = init_fmatrix(n3); list->Mlist = insertFirst(list->Mlist, m);
            }
            Function f = new Tfunction(name, b1, b2, m); list->Flist = insertFirstF(list->Flist, f);
            return list;
        } else if(choice == "expression"){
            list->Flist = command_new_function_from_representative_matrix(list->Flist);
            list = command_save_function(list);
        } else {
            cout << "Invalid choice" << endl << endl;
        }
        return list;
    } else {
        cout << "Function with the same name already exists" << endl << endl;
    }
    return list;
}

FMatrix base_change(setFVectorsPtr b1, setFVectorsPtr b2){ // ! Check if the sets are bases of the same vectorial space
    FMatrix m1 = set_vectors_to_fmatrix(b1), m2 = set_vectors_to_fmatrix(b2);
    FMatrix full = new Tfmatrix(m1->nr, (m1->nc + m2->nc));
    int r = m1->nr, c1 = m1->nc, c2 = m2->nc, tot = c1 + c2;
    for(int i = 0; i < r; i++){
        for(int j = 0; j < tot; j++){
            if(j < c1){
                //full->mat[i][j] = fraction_copy(m1->mat[i][j]);
                full->mat[i][j]->num = m2->mat[i][j]->num;
                full->mat[i][j]->den = m2->mat[i][j]->den;
            } else {
                //full->mat[i][j] = fraction_copy(m2->mat[i][j - c1]);
                full->mat[i][j]->num = m1->mat[i][j - c1]->num;
                full->mat[i][j]->den = m1->mat[i][j - c1]->den;
            }
        }
    }
    FMatrix rref = fraction_matrix_rref(full); FMatrix res = new Tfmatrix(r, c1);
    for(int i = 0; i < r; i++){
        for(int j = c1; j < tot; j++){
            res->mat[i][j - c1] = rref->mat[i][j];
        }
        cout << endl;
    }
    return res;
}

Lists command_base_change(Lists list){
    string name; cout << "Function name: "; fflush(stdin); cin >> name;
    Function f = get_fsearch(list->Flist, name);
    if(f != NULL){
        FMatrix bs; int choice; cout << "From which base to which?" << endl;
        cout << "1) " << f->b1->name << " to " << f->b2->name << endl;
        cout << "2) " << f->b2->name << " to " << f->b1->name << endl;
        cout << ">> "; fflush(stdin); cin >> choice;
        if(choice == 1){
            bs = base_change(f->b1, f->b2);
            bs->name = "M" + f->b1->name + f->b2->name;
        } else if(choice == 2){
            bs = base_change(f->b2, f->b1);
            bs->name = "M" + f->b2->name + f->b1->name;
        } else {
            cout << "Invalid choice" << endl; return list;
        }
        print_fmatrix(bs);
        list->Mlist = insertFirst(list->Mlist, bs);
        return list;
    } else {
        cout << "Function not found" << endl << endl;
    }
    return list;
}

Lists command_representative_matrix_formula(Lists list){ // ! Da fixare
    string name; cout << "Function name: "; fflush(stdin); cin >> name;
    Function f = get_fsearch(list->Flist, name);
    if(f != NULL){
        string n1, n2; cout << "Base \"from\" name >> "; fflush(stdin); cin >> n1;
        setFVectorsPtr b1, b2;
        if(isPresentS(list->Slist, n1)){
            b1 = get_ssearch(list->Slist, n1);
        } else {
            b1 = init_set_fvectors_base(n1);
            list->Slist = insertFirstS(list->Slist, b1);
        }
        cout << "Base \"to\" name >> "; fflush(stdin); cin >> n2;
        if(isPresentS(list->Slist, n2)){
            b2 = get_ssearch(list->Slist, n2);
        } else {
            b2 = init_set_fvectors_base(n2);
            list->Slist = insertFirstS(list->Slist, b2);
        } // TODO: Add a check for the bases (if they are the same)
        FMatrix m1 = base_change( f->b1 , b1), m2 = base_change(b2, f->b1);
        FMatrix tot = fraction_matrix_multiplication(fraction_matrix_multiplication(m1, f->mr), m2);
        tot->name = "M"+b1->name + "(" + f->name + ")";
        list->Mlist = insertFirst(list->Mlist, tot); print_fmatrix(tot); cout << endl;
        return list;
    } else {
        cout << "Function not found" << endl << endl;
    }
    return list;
}

// int n = b1->dim; setFVectorsPtr c1 = new TsetFVectors(b1->dim, b1->n_th, b1->name);
//         for(int i = 0; i < n; i++){
//             c1->v[i] = apply_linear_function(f, b1->v[i]);
//         }
//         FMatrix res = base_change(c1, b2); list->Mlist = insertFirst(list->Mlist, res);
//     print_fmatrix(res);