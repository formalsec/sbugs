#ifndef _LISTAJOGO_
#define _LISTAJOGO_

#include "jogo.h"
#include "listaJogo.h"

/* Estrutura node de jogo */
typedef struct nodeJogo  {
    jogo*            Jogo;
    struct nodeJogo* next;
    struct nodeJogo* previous;
} nodeJogo;

/* Estrutura lista ligada de jogos */
typedef struct  listaJogo {
    struct nodeJogo* head;
    struct nodeJogo* tail;
} listaJogo;

nodeJogo*  criaNodeJogo(jogo* Jogo, nodeJogo* next, nodeJogo* previous);
void       freeNodeJogo(nodeJogo* Node);

listaJogo* criaListaJogo();
void       freeListaJogo(listaJogo* Lista);
void       freeListaMaisJogos(listaJogo* Lista);

listaJogo* insereInicioListaJogo(listaJogo* Lista, jogo* Jogo);
listaJogo* insereFimListaJogo(listaJogo* Lista, jogo* Jogo);

jogo*      procuraListaJogo(listaJogo* Lista, char* nome);
listaJogo* removeListaJogo(listaJogo* Lista, char* nome);

void       printListaJogo(listaJogo* Lista, int* pNL);

#endif
