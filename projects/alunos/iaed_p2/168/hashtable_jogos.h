#include "Jogo.h"

void HTinic_jogos(Jogo **jogos, int dim);

void HTinsere_jogo(Jogo *jogo, Jogo **jogos, int dim);

void HTlista_jogos(Jogo **jogos, int dim, int conta_linhas);

void HTremove_jogo(Jogo *jogo, Jogo **jogos, int dim);

Jogo* HTprocura_jogo(char *nome, Jogo **jogos, int dim);

void HTfree_jogos(Jogo **jogos, int dim);