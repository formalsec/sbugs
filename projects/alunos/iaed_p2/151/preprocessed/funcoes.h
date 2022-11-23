#ifndef FUNCOES
#define FUNCOES

#include "hashtable_equipas.h"
#include "listajogos.h"
#include "hashtable_jogos.h"

/* FUNCOES PRINCIPAIS */
void adiciona_jogo(item_hash_jg* hash_jogos, linkeq* hash_equipas, lista lista_jogos, int linha);
void lista_todos_jogos(lista lista_jogos, int linha);
void procura_jogo(item_hash_jg* hash_jogos, int linha);
void apaga_jogo(item_hash_jg* hash_jogos, linkeq* hash_equipas, lista lista, int linha);
void altera_score(item_hash_jg* hash_jogos, linkeq* hash_equipas, int linha);
void adiciona_equipa(linkeq* hash_equipas, int linha);
void procura_equipa(linkeq* hash_equipas, int linha);
void lista_melhores_equipas(linkeq* hash_equipas, int linha);

/* FUNCOES AUXILIARES */
int funcao_comparacao( const void *equipa1, const void *equipa2);
int obtem_resultado(int score1, int score2);
void free_hashequipas(linkeq* hash_equipas);
void free_listajogos(lista l);
void free_hash_jogos(item_hash_jg* hash_jogos);

#endif