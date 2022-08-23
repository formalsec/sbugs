#ifndef STACK_H
#define STACK_H

#include "match.h"

struct STACKteamsnode {
    char* team;
    struct STACKteamsnode* next;
};

typedef struct STACKteamsnode* tlink; 

struct tstack {
    tlink head;
};

typedef struct tstack* tSTACK;

tSTACK tSTACKinit();
int tSTACKempty(tSTACK);
void tSTACKpush(tSTACK, char*);
char* tSTACKteamsearch(tSTACK, char*);
int tSTACKlength(tSTACK);
void tSTACKdelete(tSTACK);
#endif