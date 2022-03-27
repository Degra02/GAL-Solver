#include <iostream>
#include <all-headers.h>

#ifndef __SET_LIST_H__
#define __SET_LIST_H__

typedef struct Tbflist{
    Set b;
    Tbflist *next;

    Tbflist(){
        b = NULL; next = NULL;
    }

    Tbflist(Set _b, Tbflist *_next){
        b = _b; next = _next;
    }

    ~Tbflist(){}

}Tbflist;

typedef Tbflist *SNodeptr;

SNodeptr insertFirstS(SNodeptr n, Set b);
Set get_ssearch(SNodeptr n, string name);
SNodeptr remove_ssearch(SNodeptr n);
bool isPresentS(SNodeptr n, string name);
SNodeptr insertS(SNodeptr n, string name);
SNodeptr command_new_vectors_set(SNodeptr n);
void command_print_vectors_set(SNodeptr n);
void command_print_all_sets(SNodeptr n);
void command_set_is_base(SNodeptr n);
void command_set_is_independent(SNodeptr n);
void command_set_is_generator(SNodeptr n);
SNodeptr command_gram_schmidt(SNodeptr n);
SNodeptr command_orthogonal_complement(SNodeptr n);
SNodeptr command_base_completion(SNodeptr n);
Matrix base_change(Set b1, Set b2);

#endif
