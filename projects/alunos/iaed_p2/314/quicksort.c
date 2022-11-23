#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define exch(A, B) {char* t = A; A=B; B=t;}   /*metodo utilizado no quicksort*/

int less(char* a, char* v) {
    return (strcmp(a, v) < 0); /*criterio de ordenacao(ordem alfabetica)*/
}

int partition(char** a, int l, int r) {
    int i = l - 1;
    int j = r;
    char* v = a[r]; /*pivot*/
    while (i < j) {
        while (less(a[++i], v)); /*verifica o criterio de ordenacao do lado esquerdo do pivot*/
        while (less(v, a[--j])) {  /*verifica o criterio de ordenacao do lado direito do pivot*/
            if (j == l) { /*caso em o pivot esta na primeira posicao do vector*/
                break;
            }
        }
        if (i < j) {
            exch(a[i], a[j]); /*faz a troca*/
        }
    }
    exch(a[i], a[r]); /*coloca o pivot na sua posicao final*/
    return i; /*ponto onde partiu o vector*/
}

void quicksort(char** a, int l, int r) {
    int i;
    if (r <= l) return;
    i = partition(a, l, r);
    quicksort(a, l, i - 1);
    quicksort(a, i + 1, r);
}