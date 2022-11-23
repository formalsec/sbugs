#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include "listae.h"
#include <stdlib.h>
#include <string.h>

/* cria nova lista vazia */
liste* mk_liste() {
    liste* l = can_fail_malloc(sizeof(liste));
    l->head = NULL;
    l->last = NULL;
    return l;
}

/*liberta memoria de um nodee*/
void free_nodee(nodee* n) {
    free(n);
}

/* liberta toda a memoria associada a lista */
void free_liste(liste* l) {
    while (l->head) { /*libertar nos*/
        nodee* tmp = l->head->next;
        free_nodee(l->head);
        l->head = tmp;
    }
    free(l); /*liberta a lista*/
}

/*apaga um nodee dado*/
void apaga_nodee(liste* l, nodee* n) {
    if (n->previous == NULL) { /*se for o primeiro nodee da lista*/
        l->head = n->next;
    }
    else { /*atualizar o next do nodee anterior*/
        n->previous->next = n->next;
    }
    if (n->next == NULL) { /*se for o ultimo nodee da lista*/
        l->last = n->previous;
    }
    else { /*atualiza o previous do nodee seguinte*/
        n->next->previous = n->previous;
    }
    free_nodee(n); /*liberta o nodee dado*/
}

/*adiciona uma nova equipa a lista*/
void adiciona_e(liste* l, equipa* n) {
    nodee* nn = can_fail_malloc(sizeof(nodee));
    nn->previous = l->last; /*coloca no fim da lista*/
    nn->next = NULL;
    nn->e = n;
    if (l->last) { /*atualiza o next do node que costumava ser o ultimo*/
        l->last->next = nn;
    }
    else {  /*se ainda nao houver nada na lista*/
        l->head = nn;
    }
    l->last = nn;
}



