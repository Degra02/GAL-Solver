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
    } else {
        cout << "Function not found" << endl << endl;
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