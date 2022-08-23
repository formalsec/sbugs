#ifndef DEFS
#define DEFS

/* Tabelas de jogos e equipas */
#include "teams_ht.h"
#include "games_ht.h"
#include "games_dll.h"

#include "sorts.h"

/* Sistema */
typedef struct system_struct {
	Team * teams;		/* Hashtable de equipas */
	Game * games;		/* Hashtable de jogos */
	dlst games_dl;		/* Lista duplamente ligada de jogos */
} * System;
	
#define SIZE_HT 48611		/* Tamanho das hashtables */
#define SIZE_STR 1024		/* Tamanho dos nomes */

#endif