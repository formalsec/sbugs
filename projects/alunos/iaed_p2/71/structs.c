#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "structs.h"

int hash(char * nome)
{
    int i, chave = 0, tamanho = strlen(nome);
    for (i = 0; i != tamanho; i++)
        chave += nome[i];
    chave = (chave % MAXHASH);
    return chave;
}

void FREEjogo(Jogo jogo)
{
    free(jogo->nome);
    free(jogo);
}

void FREEjlink(jlink link)
{
    FREEjogo(link->jogo);
    free(link);
}

void FREEequipa(Equipa equipa)
{
    free(equipa->nome);
    free(equipa);
}

void FREEelink(elink link)
{
    FREEequipa(link->equipa);
    free(link);
}
