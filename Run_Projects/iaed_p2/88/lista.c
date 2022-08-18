#include "lista.h"

/* cria um novo no da lista */
no *novo_no(void *item) {

    no *no_aux = (no *) malloc(sizeof(no));
    no_aux->item = item;
    no_aux->prox = NULL;

    return no_aux;
}

/* insere um no no inicio da lista */
no *insere(no *cabeca, void *item) {

    no *no_aux = novo_no(item);

    if (cabeca == NULL) {
        return no_aux;
    }

    else {
        no_aux->prox = cabeca;
        cabeca = no_aux;
        return cabeca;
    }
}

/* remove um node associado a item da lista */
no *retira(no *cabeca, void *item, int (*igual)(void* , void*), void (*liberta_item)(void *)) {

    no *no_aux = cabeca;
    no *no_ant = NULL;

    while (no_aux != NULL) {

        if((*igual)(no_aux->item, item)){

            /* caso especial: no_ant aponta para NULL */
            if (no_aux == cabeca) {

                (*liberta_item)(no_aux->item);
                cabeca = no_aux->prox;
                free(no_aux);

                return cabeca;
            }

            else {

                no_ant->prox = no_aux->prox;
                (*liberta_item)(no_aux->item);
                free(no_aux);
                
                return cabeca;
            }

        }

        no_ant = no_aux;
        no_aux = no_aux->prox;

    }

    return cabeca;
}

/* pesquisa um item generico numa lista, e se existir, retorna-o, caso contrario, retorna NULL */
void *procura(no *cabeca, void *item, int (*igual)(void* , void*)) {

    no *no_aux;

    for (no_aux = cabeca; no_aux != NULL; no_aux = no_aux->prox) {

        if(((*igual)(no_aux->item, item))) {
            return no_aux->item;
        }
        
    }

    return NULL;
}

/* liberta a memoria associada a lista */
void liberta_lista(no *cabeca, void (*liberta_item)(void *)) {
    
    no *no_aux = cabeca;
    no *prox;

    while(no_aux != NULL) {
        prox = no_aux->prox;
        (*liberta_item)(no_aux->item);
        free(no_aux);
        no_aux = prox;
    }

}





