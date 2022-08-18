#ifndef AUX_H
#define AUX_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "HASHTABLE.h"

team_list* AlocaEquipas();

game_list* AlocaJogos();

void freeList(team_list* l); 

void freeGameList(game_list* l);

#endif
