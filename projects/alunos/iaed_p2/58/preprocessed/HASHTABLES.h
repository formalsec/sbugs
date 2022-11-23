#ifndef _HASHTABLES_
#define _HASHTABLES_

#include "jogos.h" 

/* Prototipos */
unsigned int funcao_dispersao(char *nome, unsigned int M);
pJogo *init_tab_dispersao(unsigned int M);
pJogo tab_dispersao_insere(pJogo *tab_dispersao, char *nome, char *equipa1, 
                            char *equipa2, int score1, int score2, unsigned int M);
pJogo procura_tab_dispersao(pJogo *tab_dispersao, char *nome_recebido, unsigned int M);
void apaga_tab_dispersao(pJogo *tab_dispersao, char *nome_recebido, unsigned int M);
pJogo *expande(pJogo *tab_dispersao, unsigned int M );
void free_tab_dispersao(pJogo *tab_dispersao, unsigned int M);

unsigned int funcao_tab_equipas(char *equipa);
void free_tab_equipas(link_equipa *tab_equipas);

#endif