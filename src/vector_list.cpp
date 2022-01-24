#include <iostream>
#include <ctime>
#include <bits/stdc++.h>
#include "all-headers.h"
using namespace std;

VNodeptr insertFirstV(VNodeptr n, FVector v){
    return new TVnode(v, n);
}

bool isPresentV(VNodeptr n, string name){
    if(n == NULL){
        return false;
    }
    VNodeptr t = n;
    while((t != NULL)){
        if(t->v->name == name){
            return true;
        }
        t = t->next;
    }
    return false;
}

VNodeptr remove_vsearch(VNodeptr n){
    string name;
    cout << "Vector name: "; fflush(stdin); cin >> name;
    if(n == NULL){
        return NULL;
    }
    VNodeptr t = n;
    if(n->v->name == name){
        t = n->next;
        delete n;
        return t;
    }
    while((t->next != NULL) && (t->next->v->name != name)){
        t = t->next;
    }
    if(t->next != NULL){
        VNodeptr r = t->next;
        t->next = t->next->next;
        delete r;
        return n;
    }
    return n;
}


FVector get_vsearch(VNodeptr n, string name){
    if(n == NULL){
        return NULL;
    }
    VNodeptr t = n;
    while((t != NULL) && (t->v->name != name)){
        t = t->next;
    }
    if(t == NULL){
        return NULL;
    } else {
        return t->v;
    }

}

VNodeptr insertV(VNodeptr n, string name){
    if(! isPresentV(n, name)){
        n = insertFirstV(n, init_fvector(name));
    } else {
        cout << endl << "Vector with the same name already present" << endl << endl;
    }
    return n;
}

void command_print_vector(VNodeptr n){
    string userinput; cout << "Vector name: "; fflush(stdin); cin >> userinput;
    FVector v = get_vsearch(n, userinput);
    if(v != NULL){
        v->print();
    } else {
        cout << "Vector not found" << endl << endl;
    }
}

void command_print_all_vectors(VNodeptr n){
    if(n == NULL){
        cout << "No saved vectors" << endl << endl;
    }
    VNodeptr t = n;
    while(t != NULL){
        t->v->print(); cout << endl << endl;
        t = t->next;
    }
}

VNodeptr command_new_vector(VNodeptr n){
    string name;
    cout << "Name= "; fflush(stdin); cin >> name;
    return insertV(n, name);
}

VNodeptr command_fvector_sum(VNodeptr n){
    string n1, n2; cout << "1st vector name: "; fflush(stdin); cin >> n1;
    cout << "2nd vector name: "; fflush(stdin); cin >> n2;
    FVector v1 = get_vsearch(n, n1), v2 = get_vsearch(n, n2);
    if((v1 == NULL) || (v2 == NULL)){
        cout << "Vector not found" << endl << endl; return n;
    }
    if(v1->n != v2->n){
        cout << "Sum not possible with vectors of different dimensions" << endl << endl; return n;
    }
    FVector res = new Tfvector();
    *res = *v1 + *v2;
    res->name = v1->name + "+" + v2->name;
    res->print();
    return insertFirstV(n, res);
}

VNodeptr command_fvector_difference(VNodeptr n){
    string n1, n2; cout << "1st vector name: "; fflush(stdin); cin >> n1;
    cout << "2nd vector name: "; fflush(stdin); cin >> n2;
    FVector v1 = get_vsearch(n, n1), v2 = get_vsearch(n, n2);
    if((v1 == NULL) || (v2 == NULL)){
        cout << "Vector not found" << endl << endl; return n;
    }
    if(v1->n != v2->n){
        cout << "Difference not possible with vectors of different dimensions" << endl << endl; return n;
    }
    FVector res = new Tfvector();
    *res = *v1 - *v2;
    res->name = v1->name + "-" + v2->name;
    res->print();
    return insertFirstV(n, res);   
}

void command_fvector_norm(VNodeptr n){
    string name; cout << "Vector name: "; fflush(stdin); cin >> name;
    FVector a = get_vsearch(n, name);
    if(a == NULL){
        cout << "Vector not found" << endl << endl;
        return ;
    }
    Tfraction norm = a->float_norm();
    cout << a->name << " norm = " << fvector_norm_print(&norm);
    printf("  ~  %.2f", a->float_norm()); cout << endl << endl;
}

void command_fvector_scalar_product(VNodeptr n){
    string n1, n2; cout << "1st vector name: "; fflush(stdin); cin >> n1;
    cout << "2nd vector name: "; fflush(stdin); cin >> n2;
    FVector v1 = get_vsearch(n, n1), v2 = get_vsearch(n, n2);
    if((v1 == NULL) || (v2 == NULL)){
        cout << "Vector not found" << endl << endl; exit(1);
    }
    if(v1->n != v2->n){
        cout << "Scalar product not possible with vectors of different dimensions" << endl << endl;
        return ;
    }
    
    Tfraction res = *v1 * *v2;
    cout << "Scalar product: "; res.print(); cout << " ~ "; res.print_float(); 
    cout << endl << endl;
}

void command_fvector_angle(VNodeptr n){
    string n1, n2; cout << "1st vector name: "; fflush(stdin); cin >> n1;
    cout << "2nd vector name: "; fflush(stdin); cin >> n2;
    FVector v1 = get_vsearch(n, n1), v2 = get_vsearch(n, n2);
    if((v1 == NULL) || (v2 == NULL)){
        cout << "Vector not found" << endl << endl; return ;
    }
    if(v1->n != v2->n){
        cout << "Cannot find angle between vectors of different dimensions" << endl << endl;
        return ;
    }
    cout << "Angle= " << v1->angle(*v2) << endl << endl;
}

VNodeptr command_fvector_cross_product(VNodeptr n){
    string n1, n2; cout << "1st vector name: "; fflush(stdin); cin >> n1;
    cout << "2nd vector name: "; fflush(stdin); cin >> n2;
    FVector v1 = get_vsearch(n, n1), v2 = get_vsearch(n, n2);
     if((v1 == NULL) || (v2 == NULL)){
        cout << "Vector not found" << endl << endl; return n;
    }
    if((v1->n != v2->n) || (v1->n != 3)){
        cout << "Can only calculate cross product between vectors of the 3rd dimension" << endl << endl;
        return n;
    }
    FVector res = v1->cross_product(*v2);
    res->name = v1->name + "x" + v2->name;
    res->print(); cout << endl << endl;
    return insertFirstV(n, res);
}