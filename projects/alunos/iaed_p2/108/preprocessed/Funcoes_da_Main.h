#ifndef Funcoes_da_Main_h
#define Funcoes_da_Main_h 
#include "Estruturas_e_Hash.h"

/*Chamada as funcoes que estao no main */

/* Funcao strdup da bibloteca, aloca a memoria necessaria para uma string*/
char *__strdup (const char *nome);

/*Funcao auxiliar de g, compara dois nomes e ve qual vem primeiro por ordem lexicografica */
int compara (const void * nome1, const void * nome2 );

/* Cria um novo jogo caso ele nao exista na hashtable com duas equipas existentes e um score respetivo*/
void a(int contador,int *max_jogos,int *max_equipas ,int *n_jogos, p_jogo **p_tab_j,p_equipa **p_tab_e,link *head,link *tail);

/* Procura um jogo dado um nome e devolve as suas componetes caso ele exista*/
void p(int contador,int *max_jogos,p_jogo **p_tab_j);

/* Altera um score de um jogo caso esse jogo exista*/
void s(int contador,int *max_jogos,p_jogo **p_tab_j);

/* Apaga um jogo dado um nome se ele existir */
void r(int contador,int *max_jogos,int *n_jogos,p_jogo **p_tab_j,link *head,link *tail);

/*Lista os jogos por ordem de entrada */
void l(int contador,link head);

/* Devolve a equipas que ganharam mais jogos por ordem lexicografica,e esse numero de vitorias */
void g(int contador,int n_equipas,int max_equipas,p_equipa *tab_j);

/* Adiciona uma equipa caso ela ainda nao exista */
void A(int contador,int *max_equipas,int *n_equipas,p_equipa **p_tab_e);

/* Procura uma equipa dado um nome e devolve as suas componetes caso ela exista */
void P(int contador,int *max_equipas, p_equipa **p_tab_e);

/*Funcao que da free a todos os mallocs feitos no programa */
void liberta(int max_equipas,p_equipa *tab_e,p_jogo *tab_j,link head);

#endif
