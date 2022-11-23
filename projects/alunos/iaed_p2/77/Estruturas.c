#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include "Estruturas.h"

/* Funcao que da free aos conteudos de jogo e ao proprio jogo */
void free_jogo(p_jogo jogo)
{
    free(jogo->nome);
    free(jogo->equipa1);
    free(jogo->equipa2);
    free(jogo);
}

/* Funcao que da free aos conteudos de equipa e a propria equipa */
void free_equipa(p_equipa equipa)
{
    free(equipa->nome);
    free(equipa);
}