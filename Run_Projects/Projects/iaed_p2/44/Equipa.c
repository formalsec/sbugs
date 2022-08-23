#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Equipa.h"

/*Aloca memoria para uma equipa e cria uma nova equipa na base de dados*/
equipa novaEquipa(char *nom){
    equipa e = malloc(sizeof(struct equipa));
    e->nome=malloc(sizeof(char)*(strlen(nom)+1));
    strcpy(e->nome,nom);
    e->wins=0;

    return e;
}

/*Liberta a memoria alocada para a equipa*/
void freeEquipa(equipa e){
    if(e){
        free(e->nome);
        free(e);
    }
}

/*Da print de uma equipa*/
void printEquipa(equipa e){
    if(e){
        printf("%s\n",e->nome);
    }
}