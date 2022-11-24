#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include "codigoAux.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Copia uma string origem para uma string destino */
void copia_String(char* destino, char* origem) {
    int i;

    for (i = 0; origem[i] != '\0'; i++) {
        destino[i] = origem[i];
    }
    destino[i] = '\0';
}

/* Aloca memoria para uma nova string e inicializa-a copiando a input string */
char* duplicaString(char* string) {
    char* novaString;
    novaString = (char*)can_fail_malloc((strlen(string)+1)*sizeof(char));
    
    copia_String(novaString, string);
    return novaString;
}

/* Retorna um hash value calculado a partir da string v e de um inteiro M */
int hash(char* v, int M) {
    int h, a = 31415, b=27183;

    for (h = 0; *v != '\0'; v++, a = a*b % (M-1)) {
        h = (a*h + *v) % M;
    }
    return h;
}
