#ifndef P2_HASHTABLEEQUIPA_H
#define P2_HASHTABLEEQUIPA_H

#include "itemEquipa.h"

typedef struct nodeEquipa{
    ItemEquipa item;
    struct nodeEquipa* next;
}NodeEquipa;

NodeEquipa* * headsEquipa;

/*prototipos*/
void initEquipa(int);
void insertEquipa(int,ItemEquipa);
ItemEquipa searchEquipa(int,char*);
void deleteTudoE(int);
void deleteHeadsE();
ItemEquipa * HashToArrayEquipa(int, int);
void chk_hashtableEquipa(int*,int);

#endif
