#ifndef JOGOS_LINKED_file
#define JOGOS_LINKED_file

#include "jogos_structs.h"

JOGO_LIST * cria_lista_jogos();

JOGO * cria_jogo(JOGO_LIST * lista_de_jogos, char * nome, 
                char * equipa1, char * equipa2, int score1, int score2);

void remove_jogo_linked(JOGO_LIST * lista_de_jogos, JOGO * jogo);

void destroy_jogo(JOGO * jogo);

void destroy_jogos_linked(JOGO_LIST * lista_de_jogos);

#endif 