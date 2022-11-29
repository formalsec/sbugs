#ifndef HASH_JOGOS_H
#define HASH_JOGOS_H

#include "jogos.h"

/* Cria uma hash table de procura linear */
Jogo** JNova_Hash(int max);

/* Aumenta a memoria da hash table */
Jogo** Jexpande(Jogo** Hash, int M);

/* Insere um elemento na hash table */
void JInsere_Hash(Jogo** Hash, Jogo* J, int M);

/* Encontra um elemento, dada uma chave */
Jogo* JProcura_Hash(Jogo** Hash, Chave x, int M);

/* Remove um elemento da hash table e da memoria e devolve N */
int JRemove_Hash(Jogo** Hash, Chave x, int M, int N);

/* Liberta a memoria associada 'a hash table */
void JDestroi_Hash(Jogo** Hash, Jogos* Lst);

#endif