#ifndef FUNC_H
#define FUNC_H

#include "struc.h"

int hash_key_e(char *name, lista_equipas *Hash_table[]);
int hash_key_p(char *name, lista_jogos *Hash_table[]);
int find_game(lista_jogos *l, char jogo[]);
int find_team(lista_equipas *l, char equipa[]);
void atualiza_v(lista_equipas *l, char equipa[]);
void retira_v(lista_equipas *l, char equipa[]);
void remove_jogo(node_jogos *element, lista_jogos *l);
void remove_equipa(node_equipas *element, lista_equipas *l);
void free_lista_jogos(lista_jogos *l);
void free_lista_equipas(lista_equipas *l);
void free_hash(lista_equipas *Hash_table[]);
void free_hash_j(lista_jogos *Hash_table[]);
void a(char jogo[], char equipa1[], char equipa2[], int score1, int score2, lista_jogos *l, lista_equipas *Hash_table[], int i, int j);
void a__2(char jogo[], char equipa1[], char equipa2[], int score1, int score2, lista_jogos *l);
void l(lista_jogos *l, int Contador);
void p(lista_jogos *l, char jogo[], int Contador);
void r(lista_jogos *l, char jogo[], int Contador, lista_equipas *Hash_table[]);
void r__2(lista_jogos *l, char jogo[]);
void s(char jogo[], int score1, int score2, lista_jogos *l, int Contador, lista_equipas *Hash_table[]);
void s__2(char jogo[], int score1, int score2, lista_jogos *l);
void A(char equipa[], lista_equipas *l);
void P(lista_jogos *l, char equipa[], int Contador);
int Alphabetic(char *A, char *B);
void merge(char * a[], int l, int m, int r);
void mergesort(char * a[], int l, int r);
void g(lista_equipas *Hash_table[], int Contador);

#endif