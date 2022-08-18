#ifndef ORDENAUX_H
#define ORDENAUX_H

#include "hashtable.h"

void lista_melhores_aux(lista_equipas *heads_eq,int mais_vitorias, int tamanho,int count);
int comparador(const void* a, const void* b);
void ordena( char **arr, int n);

#endif