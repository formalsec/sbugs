#ifndef CORE_H
#define CORE_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estruturas.h"
#include "constantes.h"


/*Prototipos*/
char SeparaInput(char input[MAX_INPUT], char input_separado[MAX_PARAM][MAX_STR]);

Lista *CriaLista();

Node **CriaHashTable();

Node *CriaNode(void *tipo_node);

int GeraHash(char *str);

void InsereNaHashTable(Node **hash_table, Node *node, int tipo);

void *ProcuraNaHashTable(char *nome, Node **hash_table, int tipo);

void InsereNaLista(Lista *lista, void *el, int tipo);

void *DestroiJogo(void *jogo);

void *DestroiEquipa(void *equipa);

void LimpaElemento(char *nome, Node **hash_table, Lista *lista, void *(*LimpaEl)(void *), int sel);

void LimpezaGeral(Node **hash_table, Lista *lista, void *(*LimpaEl)(void *));

#endif