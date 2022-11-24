#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "hashtable_jogos.h"

/* Funcao que inicializa a hash table dos jogos. */
item_hash_jg* HashJogos_inic(){
    int i;
    item_hash_jg* hash_jogos = (item_hash_jg*) can_fail_malloc(TAM_HASH*sizeof(item_hash_jg));
    for (i = 0; i < TAM_HASH; i++){
        hash_jogos[i] = NULL;
    }
    return hash_jogos;

}

/* Funcao que encontra o item da hash dos jogos com o ponteiro para o
jogo um determinado nome. */
item_hash_jg encontra_jogo(item_hash_jg* hash_jogos, char* nome){

    int key = hashfunc(nome);
    item_hash_jg aux = hash_jogos[key];

    while (aux != NULL){

        if (strcmp(aux->pno->jogo->nome, nome) == 0)
            return aux;
           
        aux = aux->next;
    }

    /* Se nao encontrar nenhum jogo */
    return NULL;

}

/* Funcao que insere um item na hash com o ponteiro para um determinado jogo. */
void HashJogos_insere(item_hash_jg* hash_jogos, linkjg pno){

    int key = hashfunc(pno->jogo->nome);
    item_hash_jg new = (item_hash_jg) can_fail_malloc(sizeof(struct item_hash_jogo));

    new->pno = pno;

    if (hash_jogos[key] != NULL){
        new->next = hash_jogos[key];
        new->prev = NULL;
        hash_jogos[key]->prev = new;
        hash_jogos[key] = new;
    }

    else {
        hash_jogos[key] = new;
        hash_jogos[key]->next = hash_jogos[key]->prev = NULL;
    }

}
