#ifndef _JOGOS_
#define _JOGOS_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_CAR 1024
#define MAX_TAB 512

typedef struct Jogo {
    char *nome;
    char *equipa1;
    char *equipa2;
    int score1;
    int score2;
} *pJogo; /* pJogo e um ponteiro para uma struct jogo */

typedef struct no_equipa {
    char *equipa;
    int vitorias;
    int size_e; /* tamanho do nome da equipa */
    struct no_equipa *next;
} *link_equipa; /* link_equipa e um ponteiro para uma struct no_equipa */

typedef struct no_jogo {
    pJogo jogo;
    struct no_jogo *next;
} *link_jogo; /* link_jogo e um ponteiro para uma struct no_jogo */

/* Prototipos */
link_jogo AdicionaJogo(link_equipa *tab_equipas, pJogo *tab_dispersao, 
                        link_jogo Jogos_head, int NL, unsigned int M, unsigned int *NJ);
void AdicionaEquipa(link_equipa *tab_equipas, int NL);
link_jogo ApagaJogo(link_equipa *tab_equipas, pJogo *tab_dispersao, link_jogo Jogos_head, 
                    unsigned int M, int NL, unsigned int *NJ);
void ListaJogos(link_jogo, int NL);
void ProcuraEquipa(link_equipa *tab_equipas, int NL);
void ProcuraJogo(pJogo *tab_dispersao, int NL, unsigned int M);
void AlteraPontuacao(link_equipa *tab_equipas, pJogo *tab_dispersao, int NL, unsigned int M);
int compara (const void *c_equipa1, const void *c_equipa2);
void EquipasVencedoras(link_equipa *tab_equipas, int NL);

#endif