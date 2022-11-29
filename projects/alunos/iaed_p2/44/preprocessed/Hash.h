#ifndef Hash_H
#define Hash_H

#include "Jogo.h"
#include "Equipa.h"

/*Estrutura que contem um apontador para um jogo e para a estrutura seguinte*/
typedef struct node{
    jogo j;
    struct node *next;

} *link;

/*Estrutura que contem um apontador para uma equipa e para a estrutura seguinte*/
typedef struct Enode{
    equipa e;
    struct Enode *next;

} *Elink;

int hash(char *v, int m);

link JnewNode(link next, jogo j);
jogo JsearchList(link head, Key v);
link removeJ(link head, Key k);
void JfreeHash(link head);
link* Jinit(int m);
void Jinsert(link *heads,jogo j);
jogo Jsearch(link *heads,Key v);
void Jdelete(link *heads,Key v);
void JdestroyHash(link* heads);


int getWins(Elink* tops,char team[1024]);
int TeamOrder (const void *a, const void *b);
void getMostWins(Elink* tops, int count);
Elink EnewNode(Elink next, equipa e);
equipa EsearchList(Elink top, Point v);
void EfreeHash(Elink top);
Elink* Einit(int m);
void Einsert(Elink *tops,equipa e);
equipa Esearch(Elink *tops,Point v);
void EdestroyHash(Elink* tops);

#endif