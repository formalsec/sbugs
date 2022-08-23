#include "equipa.h"
#include "abstract.h"

/* Recebe um ponteiro para equipa e liberta a memoria
 * alocada para essa equipa */
void freeEquipa(ptr_equipa a)
{
    free(key_equipa(a));
    free(a);
}

/* Recebe um nome o numero de jogos ganhos e
 * cria uma nova equipa */
ptr_equipa newEquipa(char *nome, int jogos_ganhos)
{
    ptr_equipa new = (ptr_equipa)malloc(sizeof(struct equipa)); /* Aloca memoria para a equipa */
    new->nome = malloc((strlen(nome) + 1) * sizeof(char)); /* Aloca memoria para o nome da equipa */
    strcpy(new->nome, nome);
    new->jogos_ganhos = jogos_ganhos;
    return new;
}