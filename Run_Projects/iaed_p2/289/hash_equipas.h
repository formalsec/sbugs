#ifndef HASHEQUIPAS_H
#define HASHEQUIPAS_H

#include "equipa.h"

/* Estrutura que representa uma equipa na Hash equipas */
typedef struct node_eq
{
    ptr_equipa link_team;
    struct node_eq *next;
} * link_eq;

/* Inicializa a Hash equipas */
link_eq *HT_eq_init(int m);

/* Insere uma equipa na Hash equipas */
void HT_eq_insert(ptr_equipa link_team, link_eq *heads_eq, int m);

/* Procura uma equipa na Hash equipas */
ptr_equipa HT_eq_search(Key_equipa c, link_eq *heads_eq, int m);

/* Remove uma equipa da Hash equipas */
void HT_eq_delete(ptr_equipa link_team, link_eq *heads_eq, int m);

/* Destroi a Hash equipas */
void HT_eq_destroy(link_eq *heads_eq, int m);

#endif