#ifndef _HASH_
#define _HASH_

#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#define TAMHASH 1009

/* estrutura dos jogos */
typedef struct jogo {
    
    char *nome, *equipa1, *equipa2;
    int score1, score2;

}*pJogo;

typedef struct jogo jogo;

/* estrutura dos nodes para as hashtables e a lista ligada */
typedef struct node1 {

    pJogo Jogo;
    
    struct node1 *prev, *next;

}*link1;

typedef struct node1 node1;

typedef struct node2 {

    char *equipa;
    int vitorias;
    struct node2 *prev, *next;

}*link2;

typedef struct node2 node2;

int hash(char *v, int M);

link2* STinitE(int m);

link1* STinitJ(int m);

link2 NEWE(char* buffer);

link2 insertBeginE(link2 head, char* nome);

link2 STinsertE(char* nome, link2 *hashtable, int m);

link2 lookupE(link2 head, char* nome);

link2 STsearchE(char* nome, link2 *hashtable, int m);

link1 NEWJ(char* buffer1, char* buffer2, char* buffer3, int n, int m);

link1 insertBeginJ(link1 head, char* nome, char* equipa1, char* equipa2, int score1, int score2);

link1 STinsertJ(char* nome, char* equipa1, char* equipa2, int score1, int score2, link1 *hashtable, int m);

link1 delete(link1 head, char* nome);

void STdelete(char* nome, link1 *hashtable, int m);

link1 lookupJ(link1 head, char* nome);

link1 STsearchJ(char* nome, link1 *hashtable, int m);

#endif