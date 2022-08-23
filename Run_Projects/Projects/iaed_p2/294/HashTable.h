#include "Estruturas.h"

#ifndef HASHTABLE_H
#define HASHTABLE_H

/*Prototipos funcoes da hash*/
int hash(char *v);
Hash_Jogo* hash_init_JOGOS();
Hash_Equipa* hash_init_EQUIPAS();
void hash_insercao_JOGOS(Hash_Jogo* HTJ, int Chave, Jogo* CJ);
void hash_insercao_EQUIPAS(Hash_Equipa* HTE, int Chave, Equipas* CE);
Jogo* hash_procura_Jogo(Hash_Jogo* HTJ, char *nome);
Equipas* hash_procura_Equipa(Hash_Equipa* HTE, char *nome);
Lista_Equipas* cria_lista_Equipas();
Lista_Jogos* cria_lista_Jogos();
void Liberta_HTE(Hash_Equipa* HTE);
void Liberta_HTJ(Hash_Jogo* HTJ);
void Liberta_Lista_Equipas(Lista_Equipas* CE);
void Liberta_Lista_Jogo(Lista_Jogos* CJ);

#endif