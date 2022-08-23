#ifndef HASHJOGOS_H
#define HASHJOGOS_H

#include "lista_jogos.h"

/* Estrutura que representa um node da Hashtable jogos */
typedef struct node_jg
{
    link_jogo ptr_link_jogo;
    struct node_jg *next;
} * link_jg;

/* Estrutura que representa a key de um jogo para a hash function */
typedef char *Key_jogo;

/* Definicao de key jogo */
#define key_jogo(a) (a->jogo->nome)

/* Inicializa a Hashtable jogos */
link_jg *HT_jg_init(int M);

/* Insere um jogo na Hashtable jogos */
void HT_jg_insert(link_jogo ptr_link_jogo, link_jg *heads_jg, int M);

/* Remove um jogo da Hashtable jogos */
void HT_jg_delete(link_jogo ptr_link_jogo, link_jg *heads_jg, int M);

/* Procura um jogo na Hashtable jogos */
link_jogo HT_jg_search(Key_jogo c, link_jg *heads_jg, int M);

/* Destroi a Hashtable jogos */
void HT_jg_destroy(link_jg *heads_jg, int M);

#endif