#ifndef _LISTAS_
#define _LISTAS_

#include "jogos.h"

/* Prototipos */
link_jogo novo_jogo_lista(pJogo jogo);
link_jogo insere_jogo_lista(link_jogo head, pJogo jogo);
link_jogo apaga_jogo_lista(link_jogo head, char* nome);
void free_jogos_lista(link_jogo head);

link_equipa nova_equipa_lista(char* equipa);
link_equipa procura_equipa_lista(link_equipa *tab_equipas, char* equipa);
void insere_equipa_lista(link_equipa *tab_equipas, char* equipa);

#endif