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

/*Lists command_new_function(Lists list){
    string choice;
    printf("From \x01b[1;38;5;3mexisting\x01b[0m bases and representative matrix or \x01b[1;38;5;3mnew\x01b[0m ones?: ");
    fflush(stdin); cin >> choice;
    if(choice == "existing"){
        list->Flist = command_new_function_from_representative_matrix(list->Flist);
        
    } else if(choice == "new"){
        string name; cout << "Function name: "; fflush(stdin); cin >> name;
        return insertF(n, name);
    } else {
        cout << "Invalid function call" << endl << endl;
    }
    return n;
}*/

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
    string choice, choice2, name;
    printf("From \x01b[1;38;5;3mexisting\x01b[0m bases and representative matrix or \x01b[1;38;5;3mnew\x01b[0m ones?: ");
    fflush(stdin); cin >> choice;
    if(choice == "existing"){
        cout << "Function name: "; fflush(stdin); cin >> name;
        Function f = init_function_from_saved(name, list);
        if(f != NULL){
            print_function(f);
            list->Flist = insertFirstF(list->Flist, f); return list;
        }
    } else if(choice == "new"){
        cout << "Knowing the representative matrix or not? (y/n): "; fflush(stdin); cin >> choice2;
        if(choice2 == "y"){
            string name; cout << "Function name: "; fflush(stdin); cin >> name;
            list->Flist = insertF(list->Flist, name); return list;
        } else if(choice2 == "n"){
            list->Flist = command_new_function_from_representative_matrix(list->Flist);
            return list;
        } else {
            cout << "Invalid function call" << endl << endl; return list;
        }
    } else {
        cout << "Invalid function call" << endl << endl;
    }
    return command_save_function(list);
}