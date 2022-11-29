#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "aux.h"
#include "equipa.h"

/* Funcao auxiliar que cria a equipa. */
pEquipa cria_equipa(char *n_eq)
{
    /* Ponteiro para uma variavel equipa generica. */
    pEquipa eq;

    eq=can_fail_malloc(sizeof(struct equipa));

    eq->n_eq=strdup(n_eq);

    eq->wins=0;

    return eq;
}

/* Funcao auxiliar imprime o conteudo guardado na estrutura equipa. */
void print_eq(pEquipa eq)
{
    printf("%s %d\n", eq->n_eq, eq->wins);
}

/* Funcao que liberta toda a memoria utilziada pela equipa. */
void free_eq(pEquipa eq)
{
    free(eq->n_eq);
    free(eq);
}
