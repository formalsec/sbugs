#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "equipa.h"
#include "jogo.h"
#include "HT_jogos.h"
#include "lista_jogos.h"



/* Cria e devolve uma nova lista de jogos sem elementos */
Lista_jg LSTjg_inicializa() {
    Lista_jg lista = (Lista_jg) can_fail_malloc(sizeof(struct lista));
    lista->head = NULL;
    lista->tail = NULL;
    return lista;
}



/* Recebe uma lista de jogos e um ponteiro para um jogo, e guarda-o na lista */
void LSTjg_adiciona(Lista_jg lista, Jogo jogo) {
    /* Se a lista nao tiver elementos, cria um novo no', que passa a ser a head e a tail */
    if (lista->head == NULL)
        lista->head = (lista->tail = novo_node_jg(jogo, lista->head));

    else {
        lista->tail->prox = novo_node_jg(jogo, lista->tail->prox);
        lista->tail = lista->tail->prox;
    }
}



/* Recebe o numero da linha do input e uma lista de jogos, e imprime os dados de todos os jogos
da lista por ordem */
void LSTjg_escreve(int NL, Lista_jg lista) {
    link_jg link = lista->head;

    while (link != NULL) {
        escreve_jogo(link->jogo, NL);
        link = link->prox;
    }
}



/* Recebe uma lista de jogos e um Jogo e apaga o no' da lista que o contem */
void LSTjg_apaga(Lista_jg lista, Jogo jogo){
    link_jg link, ant, head;
    head = lista->head;

    for (link=head, ant = NULL; link != NULL; ant = link, link = link->prox) {
        if (link->jogo == jogo) {
            /* Se o no' for a head, o no' seguinte passa a ser a head */
            if (link == head)
                lista->head = link->prox;
            
            else
                ant->prox = link->prox;

            /* Se o no' for a tail, o no' anterior passa a ser a tail */
            if (link == lista->tail)
                lista->tail = ant;
            
            free(link);
            break;
        }
    }     
}



/* Recebe uma lista de jogos e apaga a lista e todos os seus nos */
void LSTjg_termina(Lista_jg lista) {
    link_jg link, prox;

    for (link=lista->head; link != NULL; link = prox) {
        prox = link->prox;
        free(link);
    }
    free(lista);
}

