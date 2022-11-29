#include "hash.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Valor maximo de careteres dos nomes dos jogos e das equipas. */
#define MAX 1024

/* Prototipos das funcoes correspondentes as possiveis acoes a executar na base de dados. */
void lista_todos(int contador, pList l);
void adiciona_jogo(int contador, pHash h, pHash_e h_e, pList l);
void lista_jogo(int contador, pHash h);
void apaga_jogo(int contador, pHash h, pHash_e h_e, pList l);
void altera_score(int contador, pHash h, pHash_e h_e);
void adiciona_equipa(int contador, pHash_e h_e);
void lista_equipa(int contador, pHash_e h_e);
void lista_melhores(int contador, pHash_e h_e);
