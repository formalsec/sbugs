#ifndef __HASHTABLE__
#define __HASHTABLE__

#include <stdlib.h>
#include "lista.h"

/* tab_disp e uma tabela de 'tamanho' ponteiros para nos (listas) */
typedef struct stru_tab {
    no **tab;
    int tamanho;
} *tab_disp;

/* cria tabela */
tab_disp nova_tab(int tamanho);

/* insere e retira item */
void insere_tab(tab_disp t, void *item, void* (*chave)(void *), int (*disp)(void *, int));
void retira_tab(tab_disp t, void *item, int (*chave)(void *, int), int (*igual)(void* , void*),
                                                                   void (*liberta)(void *));

/* liberta memoria */
void liberta_tab(tab_disp t, void (*liberta_item)(void *));

/* procura item */
void* procura_tab(tab_disp t, void *chave, int (*disp)(void *, int), int (*igual)(void* , void*));

#endif


