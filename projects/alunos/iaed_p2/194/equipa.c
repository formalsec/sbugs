#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "equipa.h"
#include "processos.h"




pEquipa* EQUIPAinit(int max,pEquipa *tab) {
    int i;
    tab = (pEquipa*) can_fail_malloc(max*sizeof(pEquipa));
    for(i = 0; i<max; i++) {
        tab[i] = NULL;
    }
    return tab;
}

void EQUIPAinsert(char *nome, int contVencidos, pEquipa *tab, int max) {
    int i;
    i = goodHash(nome, max);
    while(tab[i] != NULL) {
        i = (i+1) % max;
    }

    tab[i] = (pEquipa)can_fail_malloc(sizeof(struct Equipa));
    tab[i]->nome = strdup(nome);
    tab[i]->contVencidos = contVencidos;

}


pEquipa EQUIPAseach(char *nome, pEquipa *tab, int max) {
    int i;
    i = goodHash(nome, max);
    while(tab[i] != NULL) {
        if(strcmp(tab[i]->nome, nome)==0){
            return tab[i];
        } else {
            i = (i+1) % max;
        }
    }
    return NULL;
}

int EQUIPAmaxWin(pEquipa *tab, int max) {
    int maxW=0,i;
    for(i=0; i<max;i++){
        if(tab[i]!=NULL&&tab[i]->contVencidos>maxW){
            maxW = tab[i]->contVencidos;
        }
    }
    return maxW;
}


int EQUIPAsizeOfList(int ganhos, pEquipa *tab, int max){
    int i, sizeList = 0;
    for(i=0; i<max; i++){
        if(tab[i] != NULL && tab[i]->contVencidos==ganhos) {
            sizeList++;
        } 
    }
    return sizeList;
}

void EQUIPAlist(int contComandos,int ganhos, pEquipa *tab, int max) {
    static char** str;
    int len, sizeList, j, x=0;
    sizeList = EQUIPAsizeOfList(ganhos, tab, max);
    str= (char**)can_fail_malloc(sizeof(char*)*sizeList);
    for(j=0;j<max;j++){
        if(tab[j] != NULL && tab[j]->contVencidos==ganhos) {
            len = (strlen(tab[j]->nome)+1);
            str[x] = (char*)can_fail_malloc(sizeof(char)* len);
            strcpy(str[x],tab[j]->nome);
            x++;
        }
    }
    EQUIPAsort(str, sizeList);
    EQUIPAlistPrintf(str, contComandos, sizeList, ganhos);
    free(str);
}

void EQUIPAsort(char** str,int sizeList){
    char* temp;
    int i, j;
    for (i = 0; i < sizeList; ++i) {
        for (j = i + 1; j < sizeList; ++j) {
            if (strcmp(str[i], str[j]) > 0) {
                temp = str[i];
                str[i] = str[j];
                str[j] = temp;
            }
        }
    }
}

void EQUIPAlistPrintf(char** str, int contComandos, int sizeList, int ganhos){
    int i;
    if(sizeList!=0){
        printf("%d Melhores %d\n",contComandos,ganhos);
    }
    for(i=0;i<sizeList;i++){
       printf("%d * %s\n",contComandos,str[i]); 
    }
}

pEquipa* EQUIPAexpand(pEquipa *tabE, int maxE){
    int i;
    pEquipa *t = tabE;
    tabE = EQUIPAinit(maxE,tabE);
    for(i=0;i<maxE/2;i++){
        if(t[i]!=NULL){
            EQUIPAinsert(t[i]->nome,t[i]->contVencidos,tabE,maxE);
        }
    }
    free(t);
    return tabE;
}


