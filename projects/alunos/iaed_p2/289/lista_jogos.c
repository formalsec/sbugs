#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include "lista_jogos.h"
#include "equipa.h"
#include "hash_equipas.h"
#include "hash_jogos.h"
#include "jogo.h"
#include "lista_jogos.h"

/* Inicializa a Lista duplamente ligada que contem os jogos
 * por ordem de input */
list *LS_jg_init()
{
    list *l = can_fail_calloc(1, sizeof(list));
    return l;
}

/* Insere um Jogo na Lista duplamente ligada que contem os jogos
 * por ordem de input */
link_jogo LS_jg_insert(ptr_jogo jogo, list *l)
{
    link_jogo new = can_fail_malloc(sizeof(struct node_jogo)); /*Aloca memoria para um novo node Jogo*/
    new->prev = l->last;
    new->next = NULL;
    new->jogo = jogo;
    if (l->last)
        l->last->next = new;
    else
        l->head = new;
    l->last = new;
    return new;
}

/* Remove um jogo da Lista duplamente ligada que contem os jogos
 * por ordem de input */
void LS_jg_delete(link_jogo ptr_node_jogo, list *l)
{
    if (ptr_node_jogo->prev == NULL)
    {
        l->head = ptr_node_jogo->next;
    }
    else
    {
        ptr_node_jogo->prev->next = ptr_node_jogo->next;
    }
    if (ptr_node_jogo->next == NULL)
    {
        l->last = ptr_node_jogo->prev;
    }
    else
    {
        ptr_node_jogo->next->prev = ptr_node_jogo->prev;
    }
    freeJogo(ptr_node_jogo->jogo); /* Liberta a memoria alocada para o Jogo */
    free(ptr_node_jogo);           /* Liberta a memoria alocada para o node Jogo */
}

/* Destroi a Lista duplamente ligada que contem os jogos
 * por ordem de input */
void freeList(list *l)
{
    link_jogo temp = NULL, aux = NULL;
    temp = l->head;
    while (temp != NULL)
    {
        aux = temp;
        temp = temp->next;
        freeJogo(aux->jogo);
        free(aux);
    }
    free(l);
}