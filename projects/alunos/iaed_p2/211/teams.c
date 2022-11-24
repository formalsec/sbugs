#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include "teams.h"
#include "aux.h"
#include <string.h>
#include <stdlib.h>

/* cria um no de uma equipa, adiciona-o a lista ligada de equipas e devolve esse no */
node_team * add_linked_list_team(linked_list_teams * linked_teams, char desc[], int victories){
    node_team * n = can_fail_malloc(sizeof(node_team));
    n->desc = can_fail_malloc(sizeof(char) * (strlen(desc) + 1));
    strcpy(n->desc, desc);
    n->victories = victories;
    n->next = NULL;
    if (linked_teams->last)
        linked_teams->last->next = n;
    else   /* se linked_teams->last == NULL, quer dizer que previamente nao existiam nos em linked_team */
        linked_teams->head = n;                               /* e, portanto, n passa a ser tambem head */
    linked_teams->last = n;
    return n;
}

/* cria um ptr_team que aponta para o no n, e coloca-o na hash table das equipas */
void add_hash_table_team(hash_table_teams * hash_teams, node_team * n){
    ptr_team *ptr_n = can_fail_malloc(sizeof(ptr_team));
    int hash_n = hash(n->desc, HASH_CAP_T);
    ptr_team * aux = hash_teams->nodes[hash_n];
    ptr_n->node = n;
    hash_teams->nodes[hash_n] = ptr_n;
    ptr_n->next = aux;
}

/* procura um ptr_team que aponta para o no com a descricao d e devolve esse ptr_team */
ptr_team * search_team(hash_table_teams * hash_teams, char d[]){
    int hash_n = hash(d, HASH_CAP_T);
    ptr_team *aux = hash_teams->nodes[hash_n];
    while (aux){
        if (strcmp(aux->node->desc, d) == 0)
            return aux;
        aux = aux->next;
    }
    return NULL;
}

/* procura o maior numero de vitorias das equipas e devolve esse valor */
int search_most_vict_teams(linked_list_teams * linked_teams){
    node_team *n = linked_teams->head;
    int res = 0;
    while (n){
        if (n->victories > res)
            res = n->victories;
        n = n->next;
    }
    return res;
}

/* destroi a hash table das equipas, fazendo free do seu conteudo */
void destroy_hash_teams(hash_table_teams *hash_teams){
    int i;
    for (i = 0; i < HASH_CAP_T; i++){
        ptr_team * aux;
        while (hash_teams->nodes[i]){
            aux = hash_teams->nodes[i]->next;
            free(hash_teams->nodes[i]);
            hash_teams->nodes[i] = aux;
        }
    }
    free(hash_teams);
}

/* destroi a lista ligada das equipas, fazendo free do seu conteudo */
void destroy_linked_teams(linked_list_teams *linked_teams){
    node_team *aux;
    while (linked_teams->head){
        aux = linked_teams->head->next;
        free(linked_teams->head->desc);
        free(linked_teams->head);
        linked_teams->head = aux;
    }
    free(linked_teams);
}


