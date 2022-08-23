#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "hashtable_equipas.h"

/* Tamanho maximo de uma string */
#define STR_MAX 1023

/* Tamanho da hash table */
#define TAM_HASH 1091

/* Constantes para descrever o resultado de um jogo */
#define EMPATE 0
#define VITORIA_E1 1
#define VITORIA_E2 2

/* Funcao que inicializa a hash table das equipas e retorna o
ponteiro para a hash */
linkeq* HashEquipas_inic(){
    
    int i;
    linkeq *hash_equipas = (linkeq*) malloc(TAM_HASH*sizeof(linkeq));

    for (i = 0; i < TAM_HASH; i++)
        hash_equipas[i] = NULL;
    
    return hash_equipas;

}

/* Funcao que recebe uma cadeia de caracters e atribui a esta
uma chave baseada na soma dos caracteres */
int hashfunc(char *nome){
    int res = 0, a = 127;

    for (; *nome != '\0'; nome++)
        res = (a*res + *nome) % TAM_HASH;

    return res;

}

/* Funcao que encontra o ponteiro para uma equipa na hash table */
linkeq encontra_equipa(linkeq* hash_equipas, char *nome){
    int key = hashfunc(nome);
    linkeq aux = hash_equipas[key];

    while (aux != NULL){

        if (strcmp(aux->pequipa->nome, nome) == 0)
            return aux;

        aux = aux->next;
    }

    return NULL;

}

/* Funcao que insere um deter ponteiro para um jogo na hash */
void HashEquipas_insere(linkeq* hash_equipas, equipa *pequipa, int key){

    linkeq new = (linkeq) malloc(sizeof(struct nodeeq));
 
    new->pequipa = pequipa;

    new->next = hash_equipas[key];
    hash_equipas[key] = new;

}
