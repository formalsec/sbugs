#include <string.h>
#include <stdlib.h>
#include "equipa.h"
#include "jogo.h"
#include "listas.h"

/* Equipas */

/* Cria uma lista duplamente ligada de equipas e devolve um ponteiro para a mesma */
lstEquipas criar_lst_equipas() {
    /* Reserva memoria para a lista */
    lstEquipas lista = (lstEquipas) malloc(sizeof(struct lst_equipas));

    lista->primeiro = NULL;
    lista->ultimo = NULL;
    return lista;
}

/* Adiciona a equipa ao final da lista */
void adicionar_equipa_lst(lstEquipas lista, ptrEquipa equipa) {
    linkEquipa nova_equipa;

    /* Reserva memoria para o no' da nova equipa */
    nova_equipa = (linkEquipa) malloc(sizeof(struct no_equipa));

    nova_equipa->equipa = equipa;
    nova_equipa->ant = lista->ultimo;
    nova_equipa->prox = NULL;

    /* Verifica se a lista se encontra vazia */
    if (lista->primeiro == NULL) {
        lista->primeiro = nova_equipa;
        lista->ultimo = nova_equipa;
    }
    else {
        lista->ultimo->prox = nova_equipa;
        lista->ultimo = nova_equipa;
    }
}

/* Procura na lista a equipa com o nome dado, devolvendo o no' onde esta se encontra */
linkEquipa procurar_equipa_lst(lstEquipas lista, char *nome) {
    linkEquipa aux;

    /* Percorre todas as equipas da lista */
    for (aux = lista->primeiro; aux != NULL; aux = aux->prox)
        /* Se alguma das equipas tiver o nome dado, devolve o no' onde esta se encontra */
        if (!strcmp(aux->equipa->nome, nome))
            return aux;
    
    /* Caso contrario, devolve NULL */
    return NULL;
}

/* Remove da lista a equipa que se encontra no no' dado */
void remover_equipa_lst(lstEquipas lista, linkEquipa equipa) {
    /* Se a equipa a remover for a unica na lista, a lista fica vazia */
    if (equipa == lista->primeiro && equipa == lista->ultimo) {
        lista->primeiro = NULL;
        lista->ultimo = NULL;
    }
    /* Se a equipa a remover for a primeira, apenas e' alterado o ponteiro para a primeira equipa */
    else if (equipa == lista->primeiro) {
        lista->primeiro = equipa->prox;
        lista->primeiro->ant = NULL;
    }
    /* Se a equipa a remover for a ultima, apenas e' alterado o ponteiro para a ultima equipa */
    else if (equipa == lista->ultimo) {
        lista->ultimo = equipa->ant;
        lista->ultimo->prox = NULL;
    }
    /* Se a equipa a remover se encontrar no meio da lista, apenas se alteram as equipas que se encontram antes e depois da mesma */
    else {
        equipa->ant->prox = equipa->prox;
        equipa->prox->ant = equipa->ant;
    }

    /* Liberta a memoria associada ao no' da equipa a remover */
    free(equipa);
}

/* Recebe uma lista de equipas e devolve o comprimento da mesma */
int comp_lst_equipas(lstEquipas lista) {
    int cont = 0;
    linkEquipa aux;

    for (aux = lista->primeiro; aux != NULL; aux = aux->prox)
        cont++;
    return cont;
}

/* Remove todas as equipas da lista, ficando esta vazia */
void limpar_lst_equipas(lstEquipas lista) {
    linkEquipa aux1, aux2;

    aux1 = lista->primeiro;
    /* Perocrre todas as equipas da lista, removendo os nos a elas associados */
    while (aux1 != NULL) {
        aux2 = aux1;
        aux1 = aux1->prox;
        remover_equipa_lst(lista, aux2);
    }
}

/* Recebe uma lista de equipas e liberta a memoria a ela associada */
void apagar_lst_equipas(lstEquipas lista) {
    linkEquipa aux;

    /* Percorre todas as equipas da lista e liberta a memoria associada a cada um dos seus nos */
    while(lista->primeiro != NULL) {
        aux = lista->primeiro;
        lista->primeiro = lista->primeiro->prox;
        free(aux);
    }

    /* Liberta a restante memoria associada 'a lista */
    free(lista);
}

/* Recebe uma lista de equipas e liberta a memoria associada 'a mesma e 'as suas equipas */
void apagar_lst_mais_equipas(lstEquipas lista) {
    linkEquipa aux;

    /* Percorre todas as equipas da lista e liberta a memoria associada aos nos e 'as suas equipas */
    while(lista->primeiro != NULL) {
        aux = lista->primeiro;
        lista->primeiro = lista->primeiro->prox;
        eliminar_equipa(aux->equipa);
        free(aux);
    }

    /* Liberta a restante memoria associada 'a lista */
    free(lista);
}

/* Jogos */

/* Cria uma lista duplamente ligada de jogos e devolve um ponteiro para a mesma */
lstJogos criar_lst_jogos() {
    /* Reserva memoria para a lista */
    lstJogos lista = (lstJogos) malloc(sizeof(struct lst_jogos));

    lista->primeiro = NULL;
    return lista;
}

/* Adiciona o jogo ao final da lista */
void adicionar_jogo_lst(lstJogos lista, ptrJogo jogo) {
    linkJogo novo_jogo;

    /* Reserva memoria para o no' do novo jogo */
    novo_jogo = (linkJogo) malloc(sizeof(struct no_jogo));

    novo_jogo->jogo = jogo;
    novo_jogo->prox = NULL;
    
    /* Verifica se a lista se encontra vazia */
    if (lista->primeiro == NULL) {
        novo_jogo->ant = NULL;
        lista->primeiro = novo_jogo;
        lista->ultimo = novo_jogo;
    }
    else {
        novo_jogo->ant = lista->ultimo;
        lista->ultimo->prox = novo_jogo;
        lista->ultimo = novo_jogo;
    }
}

/* Procura na lista o jogo com o nome dado, devolvendo o no' onde este se encontra */
linkJogo procurar_jogo_lst(lstJogos lista, char *nome) {
    linkJogo aux;

    /* Percorre todos os jogos da lsita */
    for (aux = lista->primeiro; aux != NULL; aux = aux->prox)
        /* Se algum dos jogos tiver o nome dado, devolve o no' onde este se encontra */
        if (!strcmp(aux->jogo->nome, nome))
            return aux;

    /* Caso contrario, devolve NULL */
    return NULL;
}

/* Remove da lista o jogo que se encontra no no' dado */
void remover_jogo_lst(lstJogos lista, linkJogo jogo) {
    /* Se o jogo a remover for o unico na lista, a lista fica vazia */
    if (jogo == lista->primeiro && jogo == lista->ultimo) {
        lista->primeiro = NULL;
        lista->ultimo = NULL;
    }
    /* Se o jogo a remover for o primeiro, apenas e' alterado o ponteiro para o primeiro jogo */
    else if (jogo == lista->primeiro) {
        lista->primeiro = jogo->prox;
        lista->primeiro->ant = NULL;
    }
    /* Se o jogo a remover for o ultimo, apenas e' alterado o ponteiro para o ultimo jogo */
    else if (jogo == lista->ultimo) {
        lista->ultimo = jogo->ant;
        lista->ultimo->prox = NULL;
    }
    else {
    /* Se o jogo a remover se encontrar no meio da lista, apenas se alteram os jogos que se encontram antes e depois do mesmo */
        jogo->ant->prox = jogo->prox;
        jogo->prox->ant = jogo->ant;
    }

    /* Liberta a memoria associada ao no' do jogo a remover */
    free(jogo);
}

/* Recebe uma lista de jogos e liberta a memoria a ela associada */
void apagar_lst_jogos(lstJogos lista) {
    linkJogo aux;

    /* Percorre todos os jogos da lista e liberta a memoria associada a cada um dos seus nos */
    while(lista->primeiro != NULL) {
        aux = lista->primeiro;
        lista->primeiro = lista->primeiro->prox;
        free(aux);
    }

    /* Liberta a restante memoria associada 'a lista */
    free(lista);
}

/* Recebe uma lista de jogos e liberta a memoria associada 'a mesma e aos seus jogos */
void apagar_lst_mais_jogos(lstJogos lista) {
    linkJogo aux;

    /* Percorre todos os jogos da lista e liberta a memoria associada aos nos e aos seus jogos */
    while(lista->primeiro != NULL) {
        aux = lista->primeiro;
        lista->primeiro = lista->primeiro->prox;
        eliminar_jogo(aux->jogo);
        free(aux);
    }

    /* Liberta a restante memoria associada 'a lista */
    free(lista);
}