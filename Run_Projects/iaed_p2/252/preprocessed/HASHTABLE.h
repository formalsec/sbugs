#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "STRUCT.h"	/* Header file que contem as estruturas utilizadas no projeto */

#define HASHSIZE 		100109  				
/* Tamanho da hashtable */

unsigned int string_hash(void *string);

void HashEquipa(team_list* l,Equipa* nova_equipa);

void HashJogo(game_list* l,Jogo* novo_jogo);

#endif
