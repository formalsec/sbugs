#ifndef NOVO_JOGO_H
#define NOVO_JOGO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "HASHTABLE.h" /* Ficheiro que contem as funcoes que gerem as hashtables */

game_list* comando_a(game_list* l, team_list* tl, int NL);

int gameErrors(char *nome_jogo,char *equipa1,char *equipa2,game_list* l, team_list* tl, int NL);

game_list* gameAdd(char *nome_jogo,char *equipa1,char *equipa2,game_list* l, team_list* tl, int NL);


#endif
