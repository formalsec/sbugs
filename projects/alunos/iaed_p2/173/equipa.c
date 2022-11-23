#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include "equipa.h"

/*
Duplica um nome (ou uma string qualquer). Aloca memoria apenas para o tamanho do nome dado
*/
char * strdup_nome(char *nome) {
    char *copia = (char*)can_fail_malloc(strlen(nome) + 1); 
    if (copia == NULL) return NULL; 
    strcpy(copia, nome);               
    return copia;                            
}

/*  
Aloca memoria para uma equipa e inicializa
*/
Equipa *cria_equipa(char *string){
    Equipa *equipa = (Equipa*) can_fail_malloc(sizeof(Equipa));
    equipa->vitorias = 0;
    equipa->nome = strdup_nome(string);
    return equipa;
}

/*  
Liberta a memoria de uma equipa
*/
void free_equipa(Equipa *equipa){
    free(equipa->nome);
    free(equipa);
}

/*
Retorna o score de uma equipa
*/
int get_score_equipa(Equipa *equipa){
    return equipa->vitorias;
}

/*
Retorna o nome de uma equipa
*/
char *get_nome_equipa(Equipa *equipa){
    return equipa->nome;
}

/* 
Soma ao score de uma equipa
*/
void alt_score_equipa(Equipa *equipa,int n){
    equipa->vitorias +=  n;
}

