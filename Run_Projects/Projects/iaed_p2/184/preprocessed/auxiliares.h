/*File generated by PreProcessor.py*/

#ifndef AUXILIARES_H
#define AUXILIARES_H

#include "jogos.h"
#include "equipas.h"


typedef struct armazena
{
  int cont;
  int max_vit;
} arm;
typedef arm *hptr;
int vencedor(int p1, int p2);
void vitorias(linkE head, int p1, int p2, char *equipa_1, char *equipa_2, hptr *h1);
void retira_pontos(linkJ jogo, linkE headE, hptr *h1);
void SelectionSort(char **nomes, int left, int right);
void aumenta(hptr *pt, int n);
#endif