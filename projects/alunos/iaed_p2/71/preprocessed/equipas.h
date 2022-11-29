#ifndef EQUIPAS_H
#define EQUIPAS_H

#include "structs.h"

/* Inicializa a hash table das equipas */
elink * init_equipas();

/* Aloca um novo elink para adicionar a hash table */
elink novo_elink(Equipa equipa, elink link);

/* Adiciona a equipa a hash table */
elink push_equipa(elink cabeca, Equipa equipa);

/* Adiciona uma equipa */
void adiciona_equipa(elink* fila2, Equipa equipa);

/* Dada uma cabeca verifica se um Jogo existe na lista da cabeca */
int existe_eq_aux(elink cabeca, char* nome);

/* Calcula qual a cabeca com que deve ser chamada existe_eq_aux() */
int existe_equipa(elink *hash_equipa, char * nome);

Equipa procura_eq_aux(elink cabeca, char* nome);

/* Igual a existe_equipa(), mas devolve uma Equipa se esta existir */
Equipa procura_equipa(elink *hash_equipa, char * nome);

/* Da free() da lista de uma certa cabeca */
elink limpa_lista_eq(elink cabeca);

/* Chama limpa_lista_eq() para todas as posicoes da hash table */
void limpa_hash_eq(elink *hash_equipa);

/* Calcula o maximo numero de jogos ganhos (record) */
int calcula_max_ganhos(elink *hash_equipa, int max);

/* Percorre a hash table, chamando calcula_max_ganhos() para cada uma das listas */
void obter_equipas(elink cabeca, Lista_Equipas lista, int max_ganhos);

#endif