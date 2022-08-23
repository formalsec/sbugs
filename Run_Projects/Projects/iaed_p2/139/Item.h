#ifndef _ITEM_H
#define _ITEM_H

/**
 * File:  Item.h
 * Item permite abstracao do tipo de dados
 * aquando da manipulacao de equipas/jogos em estruturas de dados
 * de nivel superior (HashTables ou LinkedLists)
**/

#include <stdlib.h>
#include <string.h>
#include "Objects.h"

typedef char* Key;

typedef struct Item
{
    Key value;
    union {
        Equipa *equipa;
        Jogo *jogo;
    } data;
    enum Type type;
} * Item;


#define key(A) (A->value)
#define eq(A, B) (strcmp(A,B)==0)
#define less(A,B) (strcmp(key(A),key(B)) < 0)

Item newItem(Type t, void *data);
void deleteItem(Item i);

#endif
