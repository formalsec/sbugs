#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include "jogo.h"
#include "abstract.h"
#include "equipa.h"

/* Recebe um Jogo e liberta a memoria alocada para
 * esse jogo */
void freeJogo(ptr_jogo a)
{
    free(a->nome);
    free(a);
}

/* Recebe os parametros de um jogo, aloca memoria e
 * cria um Jogo novo */
ptr_jogo newJogo(char *nome, ptr_equipa equipa1, ptr_equipa equipa2, int score1, int score2)
{
    ptr_jogo new = (ptr_jogo)can_fail_malloc(sizeof(struct jogo));  /* Aloca memoria para um jogo */
    new->nome = can_fail_malloc((strlen(nome) + 1) * sizeof(char)); /* Aloca memoria para o nome do jogo */
    strcpy(new->nome, nome);
    new->equipa1 = equipa1;
    new->equipa2 = equipa2;
    new->score1 = score1;
    new->score2 = score2;
    return new;
}