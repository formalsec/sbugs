#ifndef JOGO_H
#define JOGO_H

#include "Equipa.h"

/* Criacao do tipo do Jogo. */
typedef struct {
    char* nome;
    Equipa *equipa1, *equipa2, *vitoriosa;
    int pontuacao[2];
    unsigned long idNumber;
} Jogo;

/* Criacao do tipo da entrada da hashtable de jogos. */
typedef struct entradaJ_t {
    char *chaveJ;
    Jogo *jogo;
    struct entradaJ_t *proxJ;
} entradaJ_t;

/* Criacao do tipo de hashtable. */
typedef struct {
    entradaJ_t **entradas;
} htJ_t;

/* Funcao que cria um jogo. */
Jogo *novoJogo(char* nome, Equipa* equipa1, Equipa* equipa2, int pontos1, int pontos2);
/* Funcao que libera a memoria alocada por um jogo. */
void liberarJogo(Jogo *jogo);
/* Funcao que cria uma entrada da hashtable. */
entradaJ_t *par_htJ(char *chaveJ, Jogo *jogo);
/* Funcao que cria uma hashtable. */
htJ_t *criar_htJ(void);
/* Funcao que cria uma hash baseado em uma chave. */
int hashJ(char *chaveJ);
/* Funcao que apropria uma entrada a hashtable. */
void apropriar_htJ(htJ_t *hashtable, char *chaveJ, Jogo *jogo);
/* Funcao que retorna um jogo que eh compativel com uma chave chaveJ. */
Jogo *obter_htJ(htJ_t *hashtable, char *chaveJ);
/* Funcao que apaga uma equipa da hashtable. */
void htJ_del(htJ_t *hashtable,  char *chave);

#endif
