#ifndef SISTEMA_H
#define SISTEMA_H

#include "equipas.h"
#include "hashtable.h"
#include "jogos.h"

/* Estrutura que representa uma base de dados de jogos de futebol amigaveis. */
typedef struct {
    Jogos *jogos;     /* Todos os jogos. */
    Equipas *equipas; /* Todas as equipas. */
    hashTable *ht;    /* Tabelas de dispersao dos jogos e das equipas. */

} Sistema;

Sistema *novoSistema();          /* Devolve um sistema inicializado. */
void destroy_sistema(Sistema *); /* Liberta toda a memoria associada ao sistema. */

void adiciona_jogo(Sistema *, int);    /* Funcao associada ao comando - a. */
void lista_jogos(Sistema *, int);      /* Funcao associada ao comando - l. */
void procura_jogo(Sistema *, int);     /* Funcao associada ao comando - p. */
void apaga_jogo(Sistema *, int);       /* Funcao associada ao comando - r. */
void altera_score(Sistema *, int);     /* Funcao associada ao comando - s. */
void adiciona_equipa(Sistema *, int);  /* Funcao associada ao comando - A. */
void procura_equipa(Sistema *, int);   /* Funcao associada ao comando - P. */
void encontra_equipas(Sistema *, int); /* Funcao associada ao comando - g. */

#endif
