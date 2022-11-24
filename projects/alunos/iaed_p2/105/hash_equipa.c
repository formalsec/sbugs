#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "hash_equipa.h"
#include "hash_table.h"
#define MAX_TABELA 1000
#define MAX 1024


/*funcao que insere uma equipa na hash table*/

void inserir_tabela_equipa(equipa *j,equipa *tabela_hash_equipa[MAX_TABELA]) {
    /*encontrar a posicao a inserir a equipa*/
    int index = funcao_tabela(j->nome); 
    /*inserir no proximo espaco nulo*/
    j->next = tabela_hash_equipa[index]; 
    /*copiar a estrutura para o novo espaco*/
    tabela_hash_equipa[index] = j;
}

/*funcao que procura uma equipa na hash table*/

equipa *procura_tabela_equipa(char *nome,equipa *tabela_hash_equipa[MAX_TABELA]) {
    /*encontrar a posicao*/
    int index = funcao_tabela(nome); 
    equipa *aux = tabela_hash_equipa[index];
    while (aux != NULL && strncmp(aux->nome,nome,MAX) != 0) {
        /*percorrer a lista ate encontrar o elemento*/
        aux = aux->next;
    }
    return aux;
}

/*funcao que liberta toda a memoria usada para criar equipas*/

void apaga_mem_equipa(equipa *tabela_hash_equipa[MAX_TABELA]) {
    int i;
    for(i=0; i < MAX_TABELA; i++){
        equipa *el = tabela_hash_equipa[i];
        while(el != NULL){
            equipa *apaga = el;
            free(el->nome);
            el = el->next;
            free(apaga);
        }
    }
}
