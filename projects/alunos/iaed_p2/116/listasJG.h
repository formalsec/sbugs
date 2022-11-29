#ifndef LISTAS_EG
#define LISTAS_EG

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "EquipasEJogos.h"

typedef struct node_* Link_;

typedef struct node_{
    Jogo* jogo;
    Link_ next;
}Node_;

Link_ inicializaLista_();
Link_ addJgLista(Link_ head,Jogo* jogo);
Link_ apagaNode_(Link_ head,Jogo* jogo);
Link_ limpaLista_(Link_ head);
Jogo* procuraJogo(Link_ head, char* nome);
Jogo* obtemElem(Link_ node);
Link_ apagaNode_caso(Link_ head,Jogo* jogo);
Link_ limpaLista_caso(Link_ head);

#endif