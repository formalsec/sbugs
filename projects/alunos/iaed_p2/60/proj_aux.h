#ifndef PROJ_AUX
#define PROJ_AUX

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define M 647
#define MAX_STR 1024


typedef struct equipa {
    char *nome;
    int vitorias;
} *eq;


typedef struct jogo {
	char *nome;
    eq equipa1;
    eq equipa2;
    int score1, score2;
} *j;

/* estrutura de nos de jogos */
typedef struct node_jog {
    j jog;
    struct node_jog *next, *prev;
} *jlink;

/* estrutura de nos das equipas */
typedef struct node_eq {
    eq eq;
    struct node_eq *next;
} *elink;

typedef struct list {
    jlink head; /* no lista de jogos */
    jlink tail;
} list_j;


int hash(char *nome);
elink * init_eq();
jlink * init_jog();

eq lookup_eq(elink head, char* nome);
j lookup_j(jlink head, char* nome);

elink insertBegin_eq(elink head, eq equipa);
jlink insertBegin_j(jlink head, j jogo);
list_j * insertEndList(list_j *list_j, j jogo);

void print(jlink list_j);

void executa_a(jlink *heads_j, list_j *list_j, elink *heads_eq, int nl);
void executa_A(elink *heads_eq, int nl);

void executa_l(list_j *list_j, int nl);

void executa_p(jlink *heads_j, int nl);
void executa_P(elink *heads_eq, int nl); 

void executa_s(jlink *heads_j, int nl);


void executa_r(jlink *heads_j, list_j *list_j, int nl);
list_j delete_j(list_j list_j, char* nome);
jlink delete_jog(jlink head, char* nome);

void free_hash_eq(elink *heads_eq);
void free_list_eq(elink head);
void free_hash_jog(jlink *heads_j);
void free_list_jog(jlink head);
void free_list_j(list_j *list_j);

#endif