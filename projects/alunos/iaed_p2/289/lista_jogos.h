#ifndef LISTAJOGOS_H
#define LISTAJOGOS_H

#include "jogo.h"

/* Estrutura que representa um jogo */
typedef struct node_jogo
{
    ptr_jogo jogo;
    struct node_jogo *next, *prev;
} * link_jogo;

/* Estrutura uma lista de jogos */
typedef struct
{
    link_jogo head, last;
} list;

/* Inicializa a lista */
list *LS_jg_init();

/* Insere na lista */
link_jogo LS_jg_insert(ptr_jogo jogo, list *l);

/* Remove na lista */
void LS_jg_delete(link_jogo ptr_node_jogo, list *l);

/* Destroi a lista */
void freeList(list *l);

#endif