#ifndef LISTA_JOGO_H
#define LISTA_JOGO_H

#include "hash_jogo.h"
#include "jogo.h"

/*
estrutura lista 
lista ligada de linkJ caracterizada por:
- cabeca (head)
- cauda (tail) 
*/
typedef struct lista{
    linkJ head,tail;
}lista;

/* inicializa a lista */
lista* InitLista();
/* insere um elemento no fim da lista */
lista* InsertEndLista(pJogo j,lista * l);
/* apaga um elemento da lista */
lista* DeleteLista(char *nome,lista * l);
/* imprime a lista */
void printLista(lista *l,int nl);
/* liberta a lista */
void freeLista(lista * l);

#endif