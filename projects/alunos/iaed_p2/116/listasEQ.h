#ifndef LISTAS_EQ
#define LISTAS_EQ

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "EquipasEJogos.h"

typedef struct node* Link;

typedef struct node{
    Equipa* equipa;
    Link next;
}Node;

Link inicializaLista();
Link addEqLista(Link head,Equipa* Equipa);
Link apagaNode(Link head,Equipa* Equipa);
Link limpaLista(Link head);
Equipa* procuraEquipa(Link head, char* nome);

#endif