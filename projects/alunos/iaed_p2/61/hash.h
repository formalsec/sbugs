#ifndef _HASH_
#define _HASH_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"
/*------------------------hashtable generica------------------------*/
/*                                                                  */
/* Estrutura hashtable, cada indice tem um pointer a apontar para   */
/* uma lista                                                        */
/*------------------------------------------------------------------*/

/*-------------------------------------------------------------------*/
/* pointer para uma lista de pointers                                */
/*-------------------------------------------------------------------*/
typedef list** table_ptrs;

/*-------------------------------------------------------------------*/
/* estrutura hashtable, com um pointer para uma lista de pointers e  */
/* o tamanho da hashtable                                            */
/*-------------------------------------------------------------------*/
typedef struct _hash hashtable;

/*-------------------------------------------------------------------*/
/* inicializa hash com tamanho M, retorna pointer para a hashtable   */
/* inicializada                                                      */
/*-------------------------------------------------------------------*/
hashtable* criahash(int M);

/*-------------------------------------------------------------------*/
/* funcao dispersao, retorna um indice da hashtable correspondente ao*/
/* nome                                                              */
/*-------------------------------------------------------------------*/
int hash(char *nome, int M);

/*-------------------------------------------------------------------*/
/* insere no indice atribuido pela funcao dispercao um ptr para o    */
/* elemento                                                          */
/*-------------------------------------------------------------------*/
void inserehash(hashtable* st,Item elemento,char* nome);

/*-------------------------------------------------------------------*/
/* remove da hash, o elemento                                        */
/*-------------------------------------------------------------------*/
void removehash(hashtable* st,Item elemento,char* nome);

/*-------------------------------------------------------------------*/
/* acede ao indice correspondente a nome, retorna ptr para a lista   */
/*                                                                   */
/* -retorna um pointer para a lista onde esta nome ou NULL caso nao  */
/* tenha sido adicionado nenhum item no indice respetivo             */
/*-------------------------------------------------------------------*/
list* lehash(hashtable* st, char* nome);

/*-------------------------------------------------------------------*/
/* free da tabela hash                                               */
/*                                                                   */
/* -controlo=1: free da hastable e dos seus items                    */
/* -freeitem: corresponde a funcao para dar free ao item da hashtable*/
/* -controlo=0: free da hashtable, mas nao dos items da mesma        */
/*-------------------------------------------------------------------*/
void freehash(hashtable* st, int M, int controlo, void freeitem(Item));

/*-------------------------------------------------------------------*/
/* procura a lista da hashtable no indice i                          */
/*                                                                   */
/* -caso nao haja lista, retorna NULL                                */
/* -caso haja lista, retorna pointer para essa lista                 */
/*-------------------------------------------------------------------*/
list* indice_hastable(hashtable* st, int i);

#endif
