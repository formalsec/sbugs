#ifndef WRAPPER_FUTEBOL
#define WRAPPER_FUTEBOL

#include "hashtable.h"

/* ========================= ESTRUTURAS  ============================= */
/* ----- EQUIPA: caracterizada por um nome e o numero de jogos ganhos ----- */
typedef struct equipa {
    char *nome;
    int jogos_ganhos;
} equipa;

/* ----- ESTRUTURA DE LISTA LIGADA: para selecionar as melhores equipas ---- */
typedef struct node_equipa {
    equipa *equipa;
    struct node_equipa *next;
} node_equipa;

typedef struct lista_equipas {
    node_equipa *head;
} lista_equipas;

/* ----- JOGO: caracterizada por um nome, duas equipas e uma pontuacao (score) ----- */
typedef struct jogo {
    char *nome_equipa1, *nome_equipa2;
    int score_eq1, score_eq2;
    char *nome;
} jogo;

/* ========================= CRIACAO  ============================= */
equipa cria_equipa(char *nome, int jogos_ganhos);
jogo cria_jogo(char *nome, char *nome_equipa1, char *nome_equipa2, int score_eq1, int score_eq2);
lista_equipas cria_lista();

/* ========================= INSERCAO  ============================= */
bool insere_equipa(tabela *t, char *chave, equipa *equipa);
bool insere_jogo(tabela *t, tabela *t_equipas, char *chave, jogo *jogo);
bool insere_lista(lista_equipas *l, equipa *equipa);

/* ========================= REMOCAO  ============================= */
bool remove_equipa(tabela *t, char *chave);
bool remove_jogo(tabela *t_jogos, tabela *t_equipas, char *chave);

/* ========================= PROCURA  ============================= */
equipa *procura_equipa(tabela *t, char *chave);
jogo *procura_jogo(tabela *t, char *chave);
node_equipa *obtem_inicio_lista(lista_equipas *l);

/* ========================= DESTRUCAO ============================= */
void destroi_equipa(void *equipa_original);
void destroi_jogo(void *jogo_original);
void destroi_lista(lista_equipas *l);

/* ========================= AUXILIARES  ============================= */
bool muda_pontuacao(tabela *t_equipas, jogo *jogo, int score1, int score2);

void ordenar_lista_equipas(lista_equipas *l, lista_equipas *resultados);

#endif