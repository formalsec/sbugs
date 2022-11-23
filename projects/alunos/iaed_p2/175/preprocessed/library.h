#ifndef LIBRARY_H
#define LIBRARY_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Equipa {
    char *nome;
    int jogos_ganhos;

    struct Equipa *next;
    struct Equipa *next_ordem;
    struct Equipa *last_ordem;
} *ptr_equipa, equipa;

typedef struct Jogo {
    char *nome;
    ptr_equipa equipa1;
    ptr_equipa equipa2;
    int score1;
    int score2;

    struct Jogo *next;
    struct Jogo *last;
    struct Jogo *next_ordem;
    struct Jogo *last_ordem;
} *ptr_jogo, jogo;

/*-------------------------- Funcoes comuns a equipas e jogos ------------------------*/

int hash(char*nome, int M);
char* copia_string(char *nome);

/*-------------------------- Funcoes auxiliares dos jogos -----------------------------*/

ptr_jogo* Init_hash_jogo(int j, ptr_jogo* h_jogo);
void free_jogo(ptr_jogo ptr_j);
void free_hash_jogo (int j, ptr_jogo* h_jogo);
void ptr_ord_jogo(ptr_jogo fila,ptr_jogo ptr);
ptr_jogo percorre_fila(ptr_jogo elem,char *nome);
void add_jogo_lista(ptr_jogo* head,ptr_jogo* tail, ptr_jogo jogo);
void remove_jogo_lista(ptr_jogo* head, ptr_jogo* tail, ptr_jogo jogo);

/*-------------------------- Funcoes auxiliares das equipas ----------------------------*/

ptr_equipa* Init_hash_equipa(int e, ptr_equipa* h_equipa);
void free_equipa(ptr_equipa ptr_e);
void free_hash_equipa (int e, ptr_equipa* h_equipa);
int ptr_ord_equipa(ptr_equipa fila, ptr_equipa ptr);
ptr_equipa devolve_ptr_e(ptr_equipa fila,char* nome_e);
ptr_equipa percorre_mais(ptr_equipa posicao,ptr_equipa equipa);
ptr_equipa percorre_menos(ptr_equipa posicao,ptr_equipa equipa);
void altera_fila(ptr_equipa* head, ptr_equipa* tail, ptr_equipa equipa,int valor);
void add_equipa_lista (ptr_equipa* head, ptr_equipa* tail, ptr_equipa equipa);

/*-------------------------- Funcoes jogos -------------------------------------------*/

void novo_jogo(int NL,ptr_jogo* h_jogo,ptr_equipa* h_equipa,int j,int e, ptr_jogo* head_jogo,
 ptr_jogo* tail_jogo, ptr_equipa* head_equipa, ptr_equipa* tail_equipa);
void procura_jogo(int NL,ptr_jogo* h_jogo,int j);
void r_jogo(int NL, ptr_jogo* h_jogo, ptr_jogo* head_jogo, ptr_jogo *tail_jogo, int j,
 ptr_equipa*head_equipa, ptr_equipa*tail_equipa);
void altera_score(int NL, ptr_jogo* h_jogo, int j,ptr_equipa* head, ptr_equipa* tail);
void lista_jogos (int NL, ptr_jogo* head);

/*-------------------------- Funcoes equipas -----------------------------------------*/

void nova_equipa(int NL,ptr_equipa* h_equipa,int e,ptr_equipa*head_equipa,ptr_equipa*tail_equipa);
void procura_equipa(int NL,ptr_equipa* h_equipa,int e);
void melhores_equipas(int NL, ptr_equipa *head);

#endif