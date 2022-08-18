#ifndef __ESTRUTURASALGORITMOS__
#define __ESTRUTURASALGORITMOS__
#include "item.h"

/* Prototipos das funcoes da Queue */
lista* novaLista(int m);
lista* dupTamanhoLista(lista *q);
lista* insereFinalLista(lista *q,item item);
void libLista(lista *q);
void destroiLista(lista* q);
lista* removeItemLista(lista* q,item Item);
item procuraLista(lista* q,char *chave);

/* Prototipos das funcoes da hashtable */
tabela* novaTabela(int m);
void insereTabela(tabela* st,item Item);
void removeTabela(tabela* st,item Item);
item procuraTabela(tabela* st,Chave v);
void destroiTabela(tabela* st);

/* Prototipo da funcao de ordenacao */
void insertionSort(lista *v,int l,int r);

#endif
