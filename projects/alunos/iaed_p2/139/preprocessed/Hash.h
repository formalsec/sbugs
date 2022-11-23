#ifndef _HASH_H
#define _HASH_H

/**
 * File:  Hash.h
 * HashTable - estrutura de dados que permite procurar
 * as equipas em O(1) amortizado
**/

#include <stdio.h>
#include <stdlib.h>
#include "Item.h"
#include "LinkedList.h"
#define M 1000


typedef LinkedList* HashTable;
struct node {
	Item item;
	LinkedList* next;
};

HashTable HASHinit();
int hash(char* value);
void insert(HashTable hashtable, Item item);
void delete(HashTable hashtable, Key k);
Item search(HashTable hashtable, Key k);
void destroy_hash(HashTable hashtable);

#endif
