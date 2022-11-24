#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include "listaj.h"
#include <stdlib.h>
#include <string.h>

/* cria nova lista vazia */
listj* mk_listj() {
    listj* l = can_fail_malloc(sizeof(listj));
    l->head = NULL;
    l->last = NULL;
    return l;
}

/*liberta memoria de um nodej*/
void free_nodej(nodej* n) {
    free(n);
}

/* liberta toda a memoria associada a lista */
void free_listj(listj* l) {
    while (l->head) { /*libertar nos*/
        nodej* tmp = l->head->next;
        free_nodej(l->head);
        l->head = tmp;
    }
    free(l); /*liberta a lista*/
}

/*apaga um nodej dado*/
void apaga_nodej(listj* l, nodej* n) {
    if (n->previous == NULL) {  /*se for o primeiro nodej da lista*/
        l->head = n->next;
    }
    else { /*atualizar o next do nodej anterior*/
        n->previous->next = n->next;
    }
    if (n->next == NULL) { /*se for o ultimo nodej da lista*/
        l->last = n->previous;
    }
    else { /*atualiza o previous do nodej seguinte*/
        n->next->previous = n->previous;
    }
    free_nodej(n); /*liberta o nodej dado*/
}

/*adiciona um novo jogo a lista*/
void adiciona_j(listj* l, jogo* n) {
    nodej* nn = can_fail_malloc(sizeof(nodej));
    nn->previous = l->last; /*coloca no fim da lista*/
    nn->next = NULL;
    nn->j = n;
    if (l->last) {/*atualiza o next do node que costumava ser o ultimo*/
        l->last->next = nn;
    }
    else { /*se ainda nao houver nada na lista*/
        l->head = nn;
    }
    l->last = nn;
}



