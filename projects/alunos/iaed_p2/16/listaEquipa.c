#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include "codigoAux.h"
#include "listaEquipa.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Aloca memoria para um node de uma equipa e inicializa-o */
nodeEquipa* criaNodeEquipa(equipa* Equipa, nodeEquipa* next, nodeEquipa* previous) {
    nodeEquipa* novoNode;
    novoNode = (nodeEquipa*)can_fail_malloc(sizeof(nodeEquipa));

    novoNode->Equipa = Equipa;
    novoNode->next = next;
    novoNode->previous = previous;

    return novoNode;
}

/* Liberta a memoria associada a um nodeEquipa */
void freeNodeEquipa(nodeEquipa* Node) {
    freeEquipa(Node->Equipa);
    free(Node);
}

/* Aloca memoria para uma lista ligada de equipas e inicializa-a */
listaEquipa* criaListaEquipa() {
    listaEquipa* novaLista;
    novaLista = (listaEquipa*)can_fail_malloc(sizeof(listaEquipa));

    novaLista->head = NULL;
    novaLista->tail = NULL;

    return novaLista;
}

/* Liberta uma lista ligada de equipas e toda a memoria associada */
void freeListaEquipa(listaEquipa* Lista) {
    nodeEquipa* aux;

    /* Se a lista nao tiver sido inicializada */
    if (Lista == NULL) {
        free(Lista);
        return;
    }

    /* Se a lista estiver vazia */
    while(Lista->head != NULL) {
        aux = Lista->head;
        Lista->head = Lista->head->next;
        free(aux);
    }

    free(Lista);
}

/* Igual a freeListaEquipa mas tambem liberta a memoria associada a cada equipa */
void freeListaMaisEquipas(listaEquipa* Lista) {
    nodeEquipa* aux;

    /* Se a lista nao tiver sido inicializada */
    if (Lista == NULL) {
        free(Lista);
        return;
    }

    /* Se a lista estiver vazia */
    while(Lista->head != NULL) {
        aux = Lista->head;
        Lista->head = Lista->head->next;
        freeNodeEquipa(aux);
    }
    free(Lista);
}

/* Adiciona uma equipa ao inicio de uma lista ligada de equipas */
listaEquipa* insereInicioListaEquipa(listaEquipa* Lista, equipa* Equipa) {
    /* Se a lista nao tiver sido inicializada */
    if (Lista == NULL) {
        Lista = criaListaEquipa();
        Lista->head = (Lista->tail = criaNodeEquipa(Equipa, NULL, NULL));
        return Lista;
    }
    /* Se a lista estiver vazia */
    if (Lista->head == NULL) {
        Lista->head = (Lista->tail = criaNodeEquipa(Equipa, NULL, NULL));
        return Lista;
    }
    /* Se a lista nao for vazia */
    Lista->head->previous = criaNodeEquipa(Equipa, Lista->head, NULL);
    Lista->head = Lista->head->previous;

    return Lista;
}

/* Adiciona um jogo ao fim de uma lista ligada de jogos */
listaEquipa* insereFimListaEquipa(listaEquipa* Lista, equipa* Equipa) {
    /* Se a lista nao tiver sido inicializada */
    if (Lista == NULL) {
        Lista = criaListaEquipa();
        Lista->head = (Lista->tail = criaNodeEquipa(Equipa, NULL, NULL));
        return Lista;
    }
    /* Se a lista estiver vazia */
    if (Lista->head == NULL) {
        Lista->head = (Lista->tail = criaNodeEquipa(Equipa, NULL, NULL));
        return Lista;
    }
    /* Se a lista nao for vazia */
    Lista->tail->next = criaNodeEquipa(Equipa, NULL, Lista->tail);
    Lista->tail = Lista->tail->next;

    return Lista;
}

/* Procura uma equipa na lista ligada de equipas e retorna-a caso exista */
equipa* procuraListaEquipa(listaEquipa* Lista, char* nome) {
    nodeEquipa* auxNode;
    char*       auxNome;

    /* Se a lista nao tiver sido inicializada */
    if (Lista == NULL) {
        return NULL;
    }

    /* Se Lista for vazia retorno NULL */
    if (Lista->head == NULL) {
        return NULL;
    }

    /* Se Lista nao for vazia */
    auxNode = Lista->head;
    auxNome = auxNode->Equipa->nome;

    /* O while termina quando encontro o node com o 
        jogo que procuro ou quando chego ao fim da lista */
    while ((strcmp(auxNome, nome) != 0) && auxNode->next != NULL) {
        auxNode = auxNode->next;
        auxNome = auxNode->Equipa->nome;
    }

    /* Se nao encontrei a equipa que procurava */
    if (auxNode == NULL) {
        return NULL;
    }
    if (strcmp(auxNome, nome) != 0) {
        return NULL;
    }

    return auxNode->Equipa;
}

/* Remove uma equipa da lista ligada de equipas e retorna a lista */
listaEquipa* removeListaEquipa(listaEquipa* Lista, char* nome) {
    char* auxNome;

    /* Se a lista for vazia retorno NULL */
    if (Lista->head == NULL) {
        return NULL;
    }
    /* Se a lista nao for vazia */
    else {
        nodeEquipa* auxNode = Lista->head;
        auxNome = auxNode->Equipa->nome;

        /* O while termina quando encontro o o node com a equipa que procuro */
        while (strcmp(auxNome, nome) != 0) {
            auxNode = auxNode->next;
            auxNome = auxNode->Equipa->nome;
        }

        /* Ligo o node anterior ao seguinte e liberto o node que procurava */
        auxNode->previous->next = auxNode->next;
        auxNode->next->previous = auxNode->previous;

        free(auxNode);
        return Lista;
    }
}

/* Encontra o numero maximo de vitorias de todas as equipas no sistema */
int encontraMaxVitorias(listaEquipa* ListaDeEquipas) {
    int         max = 0;
    nodeEquipa* auxNode;

    /* Se a lista nao tiver sido inicializada ou estiver vazia */
    if (ListaDeEquipas == NULL || ListaDeEquipas->head == NULL) {
        return -1;
    }

    /* Se Lista nao for vazia */
    auxNode = ListaDeEquipas->head;

    /* O while termina quando chego ao fim da lista */
    while (auxNode != NULL) {
        if (auxNode->Equipa->numeroVitorias > max) {
            max = auxNode->Equipa->numeroVitorias;
        }
        auxNode = auxNode->next;
    }

    return max;
}
