#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include "estruturas.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*Funcao responsavel por inicializar a hash table das equipas*/
void init_HTE(equipa * HTequipa){
    int i;
    for(i = 0; i < TABLE_SIZE; i++){
        HTequipa[i] = NULL;
    }
}

/*Funcao responsavel por retornar o valor do indice da hash table dependendo do nome dado*/
int Hash(char *v, int M){
    int h, a = 31415, b = 27183;
    for (h = 0; *v != '\0'; v++, a = a*b % (M-1))
        h = (a*h + *v) % M;
    return h;
}

/*Funcao responsavel por criar uma nova equipa alocando a memoria necessaria para inserir dentro da hash table*/
equipa newequipa(char * buffer, int n){
    equipa aux = can_fail_malloc(sizeof(struct str_equipa));
    aux->nome = can_fail_malloc(sizeof(char)*(strlen(buffer)+1));
    aux->vitorias = n;
    strcpy(aux->nome,buffer);
    aux->nextE=NULL;
    return aux;
}

/*Funcao responsavel por inserir a nova equipa no inicio de cada indice da hash table*/
equipa InsertBegining(equipa head, char * nome){
    equipa aux = newequipa(nome,0);
    aux->nextE = head;
    return aux;
}

/*Funcao responsavel por obter o indice em que a nova equipa vai ser inserida*/
void InsertEquipa(char * nome, equipa * HTequipa){
    int x = Hash(nome,TABLE_SIZE);
    HTequipa[x] = InsertBegining(HTequipa[x], nome);
}

/*Funcao responsavel por procurar uma equipa dentro da hash table*/
equipa SearchEquipa(char * nome, equipa * HTequipa){
    int i = Hash(nome, TABLE_SIZE);
    equipa aux;
    for(aux = HTequipa[i]; aux != NULL; aux = aux->nextE){
        if(strcmp(aux->nome,nome) == 0) return aux;
    }return NULL;
}

/*Funcao responsavel por inserir as equipas numa lista por ordem lexicografica*/
equipa ListaEquipas(equipa lista, char * nome, int vitorias){
    equipa aux, x = newequipa(nome, vitorias);
    if (lista == NULL || strcmp(lista->nome, nome) > 0){ /*se a lista for nula ou se o jogo dado for o primeiro elemento da lista poe na cabeca da lista*/
        x->nextE = lista; 
        return x; /*devolve a nova cabeca da lista*/
    } 
    else{ 
        aux = lista; 
        /*ciclo usado para descobrir a posicao na lista do jogo dado*/
        while (aux->nextE != NULL && strcmp(aux->nextE->nome, x->nome) < 0) aux = aux->nextE; 
        x->nextE = aux->nextE; 
        aux->nextE = x;
        return lista; /*devolve a lista ordenada*/
    } 
}

/*Funcao responsavel para libertar a memoria usada pela hash table das equipas*/
void FreeHTequipa(equipa * HTequipa){
    int i;
    equipa aux;
    for(i = 0; i<TABLE_SIZE;i++ ){
       while(HTequipa[i]){
           aux = HTequipa[i]->nextE;
           FreeEquipa(HTequipa[i]); /*liberta a memoria usada em cada parametro da equipa*/
           HTequipa[i] = aux;
       }
    }
}

/*Funcao responsavel para libertar a memoria usada para criar cada parametro da equipa*/
void FreeEquipa(equipa aux){
    free(aux->nome);
    free(aux);
}

/*Funcao usada para libertar a memoria da lista usada para listar as equipas por ordem lexicografica*/
void FreeListE(equipa head){
    equipa aux;
     while(head){
           aux = head->nextE;
           FreeEquipa(head);
           head = aux;
    }
}
