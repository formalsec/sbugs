#ifndef HASH_EQUIPAS_H
#define HASH_EQUIPAS_H

#include "jogos.h"

/* Cria uma hash table de procura linear */
Equipa** ENova_Hash(int max);

/* Aumenta a memoria da hash table */
Equipa** Eexpande(Equipa** Hash, int M);

/* Insere um elemento na hash table */
void EInsere_Hash(Equipa** Hash, Equipa* E, int M);

/* Encontra um elemento, dada uma chave */
Equipa* EProcura_Hash(Equipa** Hash, Chave x, int M);

/* Liberta a memoria associada 'a hash table */
void EDestroi_Hash(Equipa** Hash, Equipas* Lst);

#endif