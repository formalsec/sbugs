#ifndef _LISTAEQUIPA_
#define _LISTAEQUIPA_

#include "equipa.h"

/* Estrutura node de equipa */
typedef struct nodeEquipa  {
    equipa* Equipa;
    struct  nodeEquipa* next;
    struct  nodeEquipa* previous;
} nodeEquipa;

/* Estrutura lista ligada de equipas */
typedef struct listaEquipa {
    struct nodeEquipa* head;
    struct nodeEquipa* tail;
} listaEquipa;

nodeEquipa*  criaNodeEquipa(equipa* Equipa, nodeEquipa* next, nodeEquipa* previous);
void         freeNodeEquipa(nodeEquipa* Node);

listaEquipa* criaListaEquipa();
void         freeListaEquipa(listaEquipa* Lista);
void         freeListaMaisEquipas(listaEquipa* Lista);

listaEquipa* insereInicioListaEquipa(listaEquipa* Lista, equipa* Equipa);
listaEquipa* insereFimListaEquipa(listaEquipa* Lista, equipa* Equipa);

equipa*      procuraListaEquipa(listaEquipa* Lista, char* nome);
listaEquipa* removeListaEquipa(listaEquipa* Lista, char* nome);

int          encontraMaxVitorias(listaEquipa* ListaDeEquipas);

#endif
