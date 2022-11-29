#ifndef JOGOS_H
#define JOGOS_H

#include "jogo.h"

struct node {
    Jogo *v;
    struct node *prev;
    struct node *next;
};

typedef struct {
    Jogo **jogos;
    int tamanho, capacidade;
    struct node *first;
    struct node *last;
} TabelaJogos;

/* Cria a tabela dos jogos */
TabelaJogos *inicia_tabela_jogos(int capacidade);
/* Insere um jogo na tabela */
void inserir_jogo(TabelaJogos *tabela, Jogo *jogo);
/* Procura um jogo por nome */
Jogo *procura_jogo(TabelaJogos *tabela, char *nome);
/* Apaga um jogo por nome */
void apagar_jogo(TabelaJogos *tabela, char *nome);
/* Liberta a memoria associada */
void free_tabela_jogos(TabelaJogos *tabela);

#endif
