#include "Estruturas.h"
#include "HashTable.h"

#ifndef FUNCOES_H
#define FUNCOES_H

/*Prototipos funcoes Principais*/
void A(Hash_Equipa* ptr_HTE, Lista_Equipas* CE, int* Contador_Instrucoes);
void a(Hash_Jogo* ptr_HTJ, Hash_Equipa* ptr_HTE, Lista_Jogos* CJ, int* Contador_Instrucoes);
void P(Hash_Equipa* ptr_HTE, int* Contador_Instrucoes);
void p(Hash_Jogo* ptr_HTJ, int* Contador_Instrucoes);
void l(Lista_Jogos* CJ, int* Contador_Instrucoes);
void s(Hash_Jogo* ptr_HTJ, Hash_Equipa* ptr_HTE, int* Contador_Instrucoes);
void g(Lista_Equipas* CE, int* Contador_Instrucoes);
void r(Hash_Jogo* ptr_HTJ, Hash_Equipa* ptr_HTE, Lista_Jogos* CJ, int* Contador_Instrucoes);

#endif