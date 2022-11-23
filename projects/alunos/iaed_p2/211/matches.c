#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include "matches.h"
#include "teams.h"
#include "aux.h"
#include <string.h>
#include <stdlib.h>

/* cria um no de um jogo, adiciona-o a lista ligada de jogos e devolve esse no */
node_match * add_linked_list_match(linked_list_matches * linked_matches, char desc[], node_team *team1, node_team *team2, int score[2]) {
    node_match * n = can_fail_malloc(sizeof(node_match));
    n->score[0] = score[0];
    n->score[1] = score[1];
    n->team1 = team1;
    n->team2 = team2;
    n->desc = can_fail_malloc(sizeof(char) * (strlen(desc) + 1));
    strcpy(n->desc, desc);
    n->prev = linked_matches->last;
    n->next = NULL;
    if (linked_matches->last)
        linked_matches->last->next = n;
    else
        linked_matches->head = n;
    linked_matches->last = n;
    return n;
}

/* cria um ptr_match que aponta para o no n, e coloca-o na hash table dos jogos */
void add_hash_table_match(hash_table_matches * hash_matches, node_match * n){
    ptr_match *ptr_n = can_fail_malloc(sizeof(ptr_match));
    int hash_n = hash(n->desc, HASH_CAP_M);
    ptr_match * aux = hash_matches->nodes[hash_n];
    ptr_n->node = n;
    hash_matches->nodes[hash_n] = ptr_n;
    if (aux)
        aux->prev = ptr_n;
    ptr_n->next = aux;
    ptr_n->prev = NULL;
}

/* procura um ptr_match que aponta para o no com a descricao d e devolve esse ptr_match */
ptr_match * search_match(hash_table_matches * hash_matches, char d[]){
    int hash_n = hash(d, HASH_CAP_M);
    ptr_match *aux = hash_matches->nodes[hash_n];
    while (aux){
        if (strcmp(aux->node->desc, d) == 0){
            return aux;
        }
        aux = aux->next;
    }
    return NULL;
}

/* remove o ptr_match ptr_n da hash tables dos jogos e devolve o no para o qual estava a apontar */
node_match * remove_match_hash_table(hash_table_matches *hash_matches, ptr_match * ptr_n){
    int hash_n = hash(ptr_n->node->desc, HASH_CAP_M);
    node_match * n = ptr_n->node;
    if (ptr_n->prev)
        ptr_n->prev->next = ptr_n->next;
    else /* ptr_n->prev == NULL, quer dizer que ptr_n era o primeiro elemento de hash_matches->nodes[hash_n]*/
        hash_matches->nodes[hash_n] = ptr_n->next;  /* logo, o primeiro elemento passa a ser o next de ptr_n*/
    if (ptr_n->next)
        ptr_n->next->prev = ptr_n->prev;
    free(ptr_n);
    return n;
}

/* remove o no n da lista ligada de jogos */
void remove_match(linked_list_matches * linked_matches, node_match *n){
    if (n->prev == NULL)
        linked_matches->head = n->next;
    else
        n->prev->next = n->next;
    if (n->next == NULL)
        linked_matches->last = n->prev;
    else
        n->next->prev = n->prev;
    free(n->desc);
    free(n);
}

/* destroi a hash table do jogos, fazendo free do seu conteudo */
void destroy_hash_matches(hash_table_matches *hash_matches){
    int i;
    for (i = 0; i < HASH_CAP_M; i++){
        ptr_match * aux;
        while (hash_matches->nodes[i]){
            aux = hash_matches->nodes[i]->next;
            free(hash_matches->nodes[i]);
            hash_matches->nodes[i] = aux;
        }
    }
    free(hash_matches);
}

/* destroi a lista ligada do jogos, fazendo free do seu conteudo */
void destroy_linked_matches(linked_list_matches *linked_matches){
    node_match *aux;
    while (linked_matches->head){
        aux = linked_matches->head->next;
        free(linked_matches->head->desc);
        free(linked_matches->head);
        linked_matches->head = aux;
    }
    free(linked_matches);
}
