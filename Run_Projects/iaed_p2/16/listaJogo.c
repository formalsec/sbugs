#include "codigoAux.h"
#include "listaJogo.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Aloca memoria para um node de um jogo e inicializa-o */
nodeJogo* criaNodeJogo(jogo* Jogo, nodeJogo* next, nodeJogo* previous) {
    nodeJogo* novoNode;
    novoNode = (nodeJogo*)malloc(sizeof(nodeJogo));

    novoNode->Jogo = Jogo;
    novoNode->next = next;
    novoNode->previous = previous;

    return novoNode;
}

/* Liberta toda a memoria associada a um nodeJogo */
void freeNodeJogo(nodeJogo* Node) {
    freeJogo(Node->Jogo);
    free(Node);
}

/* Aloca memoria para uma lista ligada de jogos e inicializa-a */
listaJogo* criaListaJogo() {
    listaJogo* novaLista;
    novaLista = (listaJogo*)malloc(sizeof(listaJogo));

    novaLista->head = NULL;
    novaLista->tail = NULL;

    return novaLista;
}

/* Liberta uma lista ligada de jogos e toda a memoria associada */
void freeListaJogo(listaJogo* Lista) {
    nodeJogo* aux;

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

/* Igual a freeListaJogo mas tambem liberta a memoria associada a cada jogo */
void freeListaMaisJogos(listaJogo* Lista) {
    nodeJogo* aux;

    /* Se a lista nao tiver sido inicializada */
    if (Lista == NULL) {
        free(Lista);
        return;
    }

    /* Se a lista estiver vazia */
    while(Lista->head != NULL) {
        aux = Lista->head;
        Lista->head = Lista->head->next;
        freeNodeJogo(aux);
    }

    free(Lista);
}

/* Adiciona um jogo ao inicio de uma lista ligada de jogos e retorna a lista */
listaJogo* insereInicioListaJogo(listaJogo* Lista, jogo* Jogo) {
    /* Se a lista nao tiver sido inicializada */
    if (Lista == NULL) {
        Lista = criaListaJogo();
        Lista->head = (Lista->tail = criaNodeJogo(Jogo, NULL, NULL));
        return Lista;
    }
    /* Se a lista estiver vazia */
    if (Lista->head == NULL) {
        Lista->head = (Lista->tail = criaNodeJogo(Jogo, NULL, NULL));
        return Lista;
    }
    /* Se a lista nao estiver vazia */
    Lista->head->previous = criaNodeJogo(Jogo, Lista->head, NULL);
    Lista->head = Lista->head->previous;
    return Lista;
}

/* Adiciona um jogo ao fim de uma lista ligada de jogos */
listaJogo* insereFimListaJogo(listaJogo* Lista, jogo* Jogo) {
    /* Se a lista nao tiver sido inicializada */
    if (Lista == NULL) {
        Lista = criaListaJogo();
        Lista->head = (Lista->tail = criaNodeJogo(Jogo, NULL, NULL));
        return Lista;
    }
    /* Se a lista estiver vazia */
    if (Lista->head == NULL) {
        Lista->head = (Lista->tail = criaNodeJogo(Jogo, NULL, NULL));
        return Lista;
    }
    /* Se a lista nao estiver vazia */
    Lista->tail->next = criaNodeJogo(Jogo, NULL, Lista->tail);
    Lista->tail = Lista->tail->next;
    return Lista;
}

/* Procura um jogo numa lista ligada de jogos e retorna-o */
jogo* procuraListaJogo(listaJogo* Lista, char* nome) {
    nodeJogo* auxNode;
    char*     auxNome;

    /* Se a lista nao tiver sido inicializada retorno NULL */
    if (Lista == NULL) {
        return NULL;
    }

    /* Se Lista for vazia retorno NULL */
    if (Lista->head == NULL) {
        return NULL;
    }

    /* Se Lista nao estiver vazia */
    auxNode = Lista->head;
    auxNome = auxNode->Jogo->nome;

    /* O while termina quando encontro o node com o 
        jogo que procuro ou quando chego ao fim da lista */
    while ((strcmp(auxNome, nome) != 0) && auxNode->next != NULL) {
        auxNode = auxNode->next;
        auxNome = auxNode->Jogo->nome;
    }

    /* Se encontra o jogo que procurava */
    if (strcmp(auxNome, nome) == 0) {
        return auxNode->Jogo;
    }

    /* Se nao encontra o jogo que procurava */
    else if (auxNode->next == NULL) {
        return NULL;
    }

    return NULL;
}

/* Remove da lista ligada de jogos o jogo com identificacao nome e retorna a lista */
listaJogo* removeListaJogo(listaJogo* Lista, char* nome) {
    nodeJogo* auxNode;
    char*     auxNome;

    /* Se a Lista nao tiver sido inicializada */
    if (Lista == NULL) {
        return NULL;
    } 
    /* Se Lista estiver vazia */
    if (Lista->head == NULL) {
        return NULL;
    }

    /* Se a lista nao estiver vazia */
    auxNode = Lista->head;
    auxNome = auxNode->Jogo->nome;

    /* O while termina quando encontro o node com o 
        jogo que procuro ou quando chego ao fim da lista */
    while ((strcmp(nome, auxNome) != 0) && auxNode->next != NULL) {
        auxNode = auxNode->next;
        auxNome = auxNode->Jogo->nome;
    }

    /* Se nao encontra o jogo que procurava */
    if (strcmp(nome, auxNome) != 0) {
        return Lista;
    }

    /* Se o auxNode eh a head e a tail */
    if (auxNode == Lista->head && auxNode == Lista->tail) {
        Lista->head = NULL;
        Lista->tail = NULL;

        free(auxNode);
        return Lista;
    }

    /* Se o auxNode eh igual a head */
    if (auxNode == Lista->head) {
        Lista->head = auxNode->next;
        Lista->head->previous = NULL;
        free(auxNode);

        return Lista;
    }

    /* Se o auxNode eh igual a tail */
    if (auxNode == Lista->tail) {
        Lista->tail = auxNode->previous;
        Lista->tail->next = NULL;
        free(auxNode);

        return Lista;
    }

    /* Ligo o node anterior ao seguinte e liberto o node que procurava */
    auxNode->previous->next = auxNode->next;
    auxNode->next->previous = auxNode->previous;

    free(auxNode);
    return Lista;
}

/* Para cada jogo da lista ligada de jogos imprime os seus parametros */
void printListaJogo(listaJogo* Lista, int* pNL) {
    nodeJogo* auxNode;

    /* Se a lista nao tiver sido inicializada ou estiver vazia */
    if (Lista->head == NULL || Lista == NULL) {
        return;
    }

    auxNode = Lista->head;

    /* Enquanto nao chego ao fim da lista */
    while (auxNode != NULL) {
        printf("%d %s %s %s %d %d\n", *pNL, 
                                    auxNode->Jogo->nome, 
                                    auxNode->Jogo->equipa1, 
                                    auxNode->Jogo->equipa2, 
                                    auxNode->Jogo->score1, 
                                    auxNode->Jogo->score2);
        auxNode = auxNode->next;
    }
}
