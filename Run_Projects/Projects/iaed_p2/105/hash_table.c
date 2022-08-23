#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash_table.h"

#define MAX_TABELA 1000
#define MAX 1024


/*funcao que determina a posicao a colocar na hash table*/

unsigned int funcao_tabela(char *nome) {
    int i;
    int comp = strlen(nome); 
    unsigned int valor_tabela = 0;
    for(i = 0; i < comp; i++) {
        /*tornar este valor o mais aleatorio possivel*/
        valor_tabela += nome[i];
        valor_tabela = (valor_tabela + nome[i]) % MAX_TABELA;
    }
    
    return valor_tabela;
}

/*funcao que insere um jogo na hash table*/

void inserir_tabela(jogo *j,jogo *tabela_hash[MAX_TABELA]) {
    /*encontrar a posicao a inserir o jogo*/
    int index = funcao_tabela(j->nome);
    /*inserir no proximo espaco nulo*/
    j->next = tabela_hash[index];
    /*copiar a estrutura para o novo espaco*/
    tabela_hash[index] = j;
}

/*funcao que procura um jogo na hash table*/

jogo *procura_tabela(char *nome,jogo *tabela_hash[MAX_TABELA]) {
    /*encontrar a posicao*/
    int index = funcao_tabela(nome); 
    jogo *aux = tabela_hash[index];
    while (aux != NULL && strncmp(aux->nome,nome,MAX) != 0) {
        /*percorrer a lista ate encontrar o elemento*/
        aux = aux->next;
    }
    return aux;
}

/*funcao que apaga um jogo da hash table*/

void apaga_tabela(char *nome,jogo *tabela_hash[MAX_TABELA]) {
    /*encontrar a posicao do jogo a remover*/
    int index = funcao_tabela(nome);

    jogo *prev; /*ponteiro para o valor anterior da lista*/
    int i = 0;

    jogo *aux = tabela_hash[index];

    while (aux != NULL) {

        if (strcmp(aux->nome, nome) == 0) {
            /*primeiro elemento sem sucessores*/
            if (aux->next == NULL && i == 0) {
                tabela_hash[index] = NULL;
            }
             
            /*primeiro elemento com sucessores*/
            else if (aux->next != NULL && i == 0) {
                tabela_hash[index] = aux->next;
            }
            
            /*ultimo elemento*/
            else if (aux->next == NULL && i != 0) {
                prev->next = NULL;
            }
            
            /*elemento do meio*/
            else if (aux->next != NULL && i != 0) {
                prev->next = aux->next;
            }

            /*libertar memoria*/
            free(aux->nome);
            free(aux->equipa1);
            free(aux->equipa2);
            free(aux);

            return;
        }
        
        /*todos os elementos descem um indice*/
        prev = aux; 
        aux = prev->next;
        ++i;
    }

}

/*funcao que liberta toda a memoria usada para criar os jogos*/

void apaga_mem_jogo(jogo *tabela_hash[MAX_TABELA]) {
    int i;
    for(i=0; i < MAX_TABELA; i++){
        jogo *el = tabela_hash[i];
        while(el != NULL){
            jogo *apaga = el;
            free(el->nome);
            free(el->equipa1);
            free(el->equipa2);
            el = el->next;
            if (apaga != NULL) {
                free(apaga);
            }
        }
    }
}

