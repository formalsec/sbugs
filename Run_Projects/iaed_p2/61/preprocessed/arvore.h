#ifndef _TREE_
#define _TREE_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*-------------------------------------------------------------------*/
/* estrutura de node da arvore, com um item e dois pointer para      */
/* outros dois nodes de arvore um a direita e outro a esquerda       */
/*-------------------------------------------------------------------*/
typedef struct _nodetree nodetree;

/*-------------------------------------------------------------------*/
/* pointer char para o item de cada node da arvore                   */
/*-------------------------------------------------------------------*/
typedef char* ItemT;

/*-------------------------------------------------------------------*/
/* cria node da arvore                                               */
/* -retorna pointer para o node                                      */
/*-------------------------------------------------------------------*/
nodetree* cria_nodetree(ItemT item);

/*-------------------------------------------------------------------*/
/* insere um novo item na arvore                                     */
/* -retorna um pointer para a head da arvore                         */
/*-------------------------------------------------------------------*/
nodetree* insere_tree(nodetree* nt, ItemT item);

/*-------------------------------------------------------------------*/
/*retorna pointer para a nodetree a esquerda de node dado            */
/*-------------------------------------------------------------------*/
nodetree* nodetree_left(nodetree* nt);

/*-------------------------------------------------------------------*/
/*retorna pointer para a nodetree a esquerda de node dado            */
/*-------------------------------------------------------------------*/
nodetree* nodetree_right(nodetree* nt);

/*-------------------------------------------------------------------*/
/*retorna pointer para a char a esquerda de node dado                */
/*-------------------------------------------------------------------*/
ItemT nodetree_item(nodetree* nt);

#endif
