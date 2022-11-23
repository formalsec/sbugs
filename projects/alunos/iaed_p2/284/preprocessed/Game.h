#ifndef GAME_H
#define GAME_H

#include "Team.h"

typedef struct Game {
	char* name;				/* nome do jogo */
	team* t1;				/* ponteiro para a estrutura da 1a equipa */
	team* t2;				/* ponteiro para a estrutura da 2a equipa */
	int s1;					/* score da 1a equipa */
	int s2;					/* score da 2a equipa */
} game;

#endif /* GAME_H */

