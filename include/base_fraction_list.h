#include <iostream>
#include <all-headers.h>

#ifndef __BASE_FRACTION_LIST_H__
#define __BASE_FRACTION_LIST_H__

typedef struct Tbflist{
    FBase b;
    Tbflist *next;

    Tbflist(){
        b = NULL; next = NULL;
    }

    Tbflist(FBase _b, Tbflist *_next){
        b = _b; next = _next;
    }

    ~Tbflist(){}

}Tbflist;

typedef Tbflist *BNodeptr;

BNodeptr insertFirstB(BNodeptr n, FBase b);
BNodeptr remove_bsearch(BNodeptr n);
bool isPresentB(BNodeptr n, string name);
BNodeptr insertB(BNodeptr n, string name);
BNodeptr command_new_base(BNodeptr n);
void command_print_base(BNodeptr n);

#endif
