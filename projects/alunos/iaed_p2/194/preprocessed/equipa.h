#ifndef EQUIPA_H
#define EQUIPA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ponteiro da equipa*/
typedef struct Equipa{ 
    char *nome;
    int contVencidos;
}*pEquipa;

/* inicializa o hashTable da equipa*/
pEquipa* EQUIPAinit(int max, pEquipa *tab);
/* adiciona a equipa na lista */
void EQUIPAinsert(char *nome, int contVencidos, pEquipa *tab, int max);
/* procura uma equipa em hashTable */
pEquipa EQUIPAseach(char *nome, pEquipa *tab, int max);
/* encontra as equipas que ganharam mais jogos e lista por ordem lexicografica (do nome da equipa) */
void EQUIPAlist(int contComandos,int ganhos, pEquipa *tab, int max);
/* encontra maximos ganhos */
int EQUIPAmaxWin(pEquipa *tab, int max);
/* enconta a quantidade das equipas que ganharam mais jogos*/
int EQUIPAsizeOfList(int ganhos, pEquipa *tab, int max);
/* lista por ordem lexicografica */
void EQUIPAsort(char** str,int sizeList);
/* printf a lista*/
void EQUIPAlistPrintf(char** str, int contComandos,int sizeList,int ganhos);
/* expande o hashTable */
pEquipa* EQUIPAexpand(pEquipa *tabE, int maxE);



#endif
