#include <iostream>
#include <ctime>
#include <bits/stdc++.h>
#include "all-headers.h"
#include "jacobi_pd.hpp"
using namespace jacobi_pd;

Lists command_new_system(Lists list){ // also saves every element of the system in the corresponding list
    string name; cout << "Name= "; fflush(stdin); cin >> name;
    if(!isPresentE(list->Eqlist, name)){
        Matrix m; Vector v;
        string mn, vn; cout << "Coefficients matrix name: "; fflush(stdin); cin >> mn;
        if(isPresent(list->Mlist, mn)){
            m = get_search(list->Mlist, mn);
        } else {
            m = init_fmatrix(mn); list->Mlist = insertFirst(list->Mlist, m);
        }
        cout << "Vector name: "; fflush(stdin); cin >> vn;
        if(isPresentV(list->Vlist, vn)){
            v = get_vsearch(list->Vlist, vn);
            if(v->n != m->nr){
                cout << "The selected vector is incompatible with the selected matrix" << endl << endl;
                return list;
            }
        } else {
            v = init_fvector_system(vn, m->nr); list->Vlist = insertFirstV(list->Vlist, v);
        }
        FEqsys s = new Tfeqsys(m, v); s->name = name;
        list->Eqlist = insertFirstE(list->Eqlist, s);
        print_feqsys(s);
    } else {
        cout << "System with the same name already present" << endl << endl;
    }
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
    string n1, n2; cout << "Function name: "; fflush(stdin); cin >> n1;
    Function f = get_fsearch(list->Flist, n1);
    if(f != NULL){
        cout << "Vector name: "; cin >> n2; Vector v;
        if(isPresentV(list->Vlist, n2)){
            v = get_vsearch(list->Vlist, n2);
        } else {
            cout << "Vector dimension: " << f->b1->n_th << endl;
            v = init_fvector_system(n2, f->b1->n_th); list->Vlist = insertFirstV(list->Vlist, v);
        }
        Vector vf = apply_linear_function(f, v); vf->name = f->name + "(" + v->name + ")";
        print_fvector(vf); list->Vlist = insertFirstV(list->Vlist, vf);
        return list;
    } else {
        cout << "Function not found" << endl << endl;
    }
    return list;
}

Lists command_function_ker(Lists list){
    string name; cout << "Function name: "; fflush(stdin); cin >> name;
    Function f = get_fsearch(list->Flist, name);
    if(f != NULL){
        Set k = Ker(f); k->name = "ker(" + f->name + ")";
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
        Set i = Im(f); i->name = "im(" + f->name + ")";
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
            Vector v = get_vsearch(list->Vlist, vname);
            Set cim = Counter_Im(f, v);
            cim->name = v->name + "cim"; // stands for counter image
            list->Slist = insertFirstS(list->Slist, cim);
            print_set_fvectors(cim); cout << endl;
        } else {
            cout << "Vector dimension: " << f->mr->nr;
            Vector v = init_fvector_system(name, f->mr->nr);
            Set cim = Counter_Im(f, v);
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

Lists command_new_function_from_representative_matrix(Lists list){
    string name, n1, n2; cout << "Function name: "; fflush(stdin); cin >> name;
    if(! isPresentF(list->Flist, name)){
        Set b1, b2;
        cout << "Base \"from\": "; fflush(stdin); cin >> n1;
        if(isPresentS(list->Slist, n1)){
            b1 = get_ssearch(list->Slist, n1);
        } else {
            b1 = init_set_fvectors(n1); list->Slist = insertFirstS(list->Slist, b1);
        }
        cout << "Base \"to\": "; fflush(stdin); cin >> n2;
        if(isPresentS(list->Slist, n2)){
            b2 = get_ssearch(list->Slist, n2);
        } else {
            b2 = init_set_fvectors(n2); list->Slist = insertFirstS(list->Slist, b2);
        }
        Function f = new Tfunction(name, b1, b2);
        f->mr = translate_linear_function(b1->n_th, b2->n_th); 
        f->mr->name = "M" + f->b1->name + f->b2->name + "(" + f->name + ")"; 
        list->Mlist = insertFirst(list->Mlist, f->mr);
        cout << endl; print_function(f); cout << endl;
        list->Flist = insertFirstF(list->Flist, f);
    } else {
        cout << "Function with the same name already exists" << endl << endl;
    }
    return list;
}

Lists command_new_function(Lists list){
    string choice; cout << "Function in \x01b[1;38;5;3mexpression\x01b[0m form or \x01b[1;38;5;3mmatrix\x01b[0m?: ";
    fflush(stdin); cin >> choice;
    if(choice == "matrix"){
        string name; cout << "Function name: "; fflush(stdin); cin >> name;
        if(! isPresentF(list->Flist, name)){
            string n1, n2, n3; cout << "Base \"from\": "; fflush(stdin); cin >> n1;
            Set b1, b2; Matrix m;
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
            cout << "Representative matrix name: "; fflush(stdin); cin >> n3;
            if(isPresent(list->Mlist, n3)){
                m = get_search(list->Mlist, n3);
                if((m->nc != b1->n_th) || (m->nr != b2->n_th)){
                    cout << "Incompatible matrix" << endl << endl; return list;
                }
            } else {
                cout << "Rows= " << b1->n_th << endl << "Columns= " << b2->n_th << endl << endl;
                m = init_fmatrix_known_dim(n3, b1->n_th, b2->n_th); list->Mlist = insertFirst(list->Mlist, m);
            }
            Function f = new Tfunction(name, b1, b2, m); list->Flist = insertFirstF(list->Flist, f);
            return list; 
        } else {
            cout << "Function with the same naem already exists" << endl << endl; return list;
        }
    } else if(choice == "expression"){
        list = command_new_function_from_representative_matrix(list);
    } else {
        cout << "Invalid choice" << endl << endl;
    }
    return list;
}

Lists command_base_change(Lists list){
    string n1, n2; cout << "1st set name: "; fflush(stdin); cin >> n1;
    Set b1, b2;
    if(isPresentS(list->Slist, n1)){
        b1 = get_ssearch(list->Slist, n1);
    } else {
        b1 = init_set_fvectors(n1); list->Slist = insertFirstS(list->Slist, b1);
    }
    cout << "2nd set name: "; fflush(stdin); cin >> n2;
    if(isPresentS(list->Slist, n2)){
        b2 = get_ssearch(list->Slist, n2);
    } else {
        b2 = init_set_fvectors(n2); list->Slist = insertFirstS(list->Slist, b2);
    }

    Matrix bc = base_change(b1, b2); bc->name = "M" + b1->name + b2->name;
    print_fmatrix(bc); cout << endl << endl;
    if(!isPresent(list->Mlist, bc->name)){
        list->Mlist = insertFirst(list->Mlist, bc);
    } else {
        cout << "Matrix already calculated" << endl << endl;
    }
    return list;
}

Lists command_representative_matrix_formula(Lists list){
    string name; cout << "Function name: "; fflush(stdin); cin >> name;
    Function f = get_fsearch(list->Flist, name);
    if(f != NULL){
        string n1, n2; cout << "Base \"from\" name >> "; fflush(stdin); cin >> n1;
        Set b1, b2;
        if(isPresentS(list->Slist, n1)){
            b1 = get_ssearch(list->Slist, n1);
        } else {
            cout << "Vector dimension: " << f->b1->n_th << endl;
            b1 = init_set_fvectors_base_function(n1, f->b1->n_th);
            list->Slist = insertFirstS(list->Slist, b1);
        }
        cout << "Base \"to\" name >> "; fflush(stdin); cin >> n2;
        if(isPresentS(list->Slist, n2)){
            b2 = get_ssearch(list->Slist, n2);
        } else {
            cout << "Vector dimension: " << f->b1->n_th << endl;
            b2 = init_set_fvectors_base_function(n2, f->b1->n_th);
            list->Slist = insertFirstS(list->Slist, b2);
        } 
        if(b1->name == b2->name){
            Matrix m1 = base_change( f->b1 , b1), m2 = base_change(b2, f->b1);
            Matrix tot = fraction_matrix_multiplication(fraction_matrix_multiplication(m1, f->mr), m2);
            tot->name = "M"+b1->name + "(" + f->name + ")";
            list->Mlist = insertFirst(list->Mlist, tot); print_fmatrix(tot); cout << endl;
        } else {
            Set app = new TsetFVectors(b1->dim, b1->dim);
            for(int i = 0; i < b1->dim; i++){
                app->v[i] = apply_linear_function(f, b1->v[i]);
            }
            Matrix res = base_change(app, b2);
            res->name = "M"+b1->name+b2->name+"("+f->name+")";
            list->Mlist = insertFirst(list->Mlist, res); print_fmatrix(res); cout << endl;
        }
        return list;
    } else {
        cout << "Function not found" << endl << endl;
    }
    return list;
}

Lists command_system_solution(Lists list){
    string userinput; cout << "System name: "; fflush(stdin); cin >> userinput;
    FEqsys eq = get_esearch(list->Eqlist, userinput); Set sol; Trc t;
    if(eq != NULL){
        t = Rouche_Capelli(eq);
        if(t == NO_RESULT){
            cout << endl << "The system has no solution" << endl << endl; return list;
        } else if(t == INF_RESULTS){
            cout << endl << "Infinite solutions, linear combination of the following set:" << endl << endl;
            sol = feq_sys_sol(eq);
        } else {
            cout << endl << "One solution" << endl << endl; sol = feq_sys_sol(eq);
        }
    } else {
        cout << "No such system" << endl << endl; return list;
    }
    sol->name = eq->name + "S"; print_set_fvectors(sol); 
    list->Slist = insertFirstS(list->Slist, sol);
    return list;
}

Lists command_find_eigenvalues(Lists list){
    string name; cout << "Function name: "; fflush(stdin); cin >> name;
    Function f = get_fsearch(list->Flist, name);
    if(f != NULL){
        Matrix m = check_matrix_symmetry(f->mr, f->b1, f->b2);
        if(m != NULL){
            int n = f->mr->nr;
            double** dm = fraction_matrix_to_float(f->mr);
            double* eigenvalues = new double[n];
            double** eigenvectors = new double*[n];
            for(int i = 0; i < n; i++){
                eigenvectors[i] = new double[n];
            }
            Jacobi<double, double*, double**> eigen_calc(n);
            if(eigen_calc.Diagonalize(dm, eigenvalues, eigenvectors) > 0){
                cout << endl << "Eigenvalues: " << endl << endl;
                for(int i = 0; i < n; i++){
                    printf("%.5f ", eigenvalues[i]);
                }
                cout << endl << endl << "Eigenvectors: " << endl << endl;
                for(int i = 0; i < n; i++){
                    for(int j = 0; j < n; j++){
                        printf(" %4.5f ", eigenvectors[i][j]);
                    }
                    cout << endl;
                }
                cout << endl << endl;

                return list;
            } else {
                cout << endl << "Convergence failed" << endl << endl;
                return list;
            }

        } else {
            return list;
        }
    }
    return list;
}
