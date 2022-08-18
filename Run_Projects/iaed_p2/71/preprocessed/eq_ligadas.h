#ifndef EQ_LIGADAS_H
#define EQ_LIGADAS_H

#include "structs.h"

/* Inicializa a lista ligada de links com equipas */
Lista_Equipas init_lista_eq();

/* Acrescenta um link a lista ligada por ordem lexicografica */
void acrescenta_eq(Lista_Equipas lista, Equipa equipa);

/* Da print aos nomes das equipas da lista ligada */
void print_lista_eq(Lista_Equipas lista, int linha, int max_ganhos);

/* Da free() a lista ligada e aos seus elementos */
void destroi_eq_ligadas(Lista_Equipas lista);

#endif