#ifndef JOGOS_H
#define JOGOS_H

#include "structs.h"

/* inicia a hash table de jogos */
jlink * init_jogos();

/* Aloca um novo jlink para adicionar a hash table */
jlink novo_jlink(Jogo jogo, jlink prox_link);

/* Adiciona um jogo a hash table */
jlink push_jogo(jlink cabeca, Jogo jogo);

/* Adiciona um jogo */
void adiciona_jogo(jlink* hash_jogos, Lista_Jogos lista, Jogo jogo);

/* Remove jogo da hash table */
jlink rem_aux2(jlink cabeca, Jogo jogo);

/* Apaga um jogo */
void remove_jogo(jlink* hash_jogos, Lista_Jogos lista, Jogo jogo);

/* Dada uma cabeca verifica se um Jogo existe na lista da cabeca */
int existe_jogo_aux(jlink cabeca, char* nome);

/* Calcula qual a cabeca com que deve ser chamada existe_jogo_aux() */
int existe_jogo(jlink *hash_jogos, char * nome);

Jogo procura_jogo_aux(jlink cabeca, char* nome);

/* Igual a existe_jogo(), mas devolve um Jogo se este existir */
Jogo procura_jogo(jlink* hash_jogos, char* nome);

/* Da free() da lista de uma certa cabeca */
jlink limpa_lista_jogos(jlink cabeca);

/* Chama limpa_lista_eq() para todas as posicoes da hash table */
void limpa_hash_jogos(jlink *hash_jogos);

#endif