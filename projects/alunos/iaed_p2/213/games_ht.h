#ifndef SIZE_HT
#define SIZE_HT 48611
#endif

#ifndef GAMES_HT
#define GAMES_HT

/* Declaracoes relacionadas com a estrutura Game */
#include "game.h"

/* Funcao de hashing */
#include "hash.h"


/* Prototipos de funcoes da hashtable de jogos */
Game * G_init();
void G_insert(Game * games, Game g);
Game G_search(Game * games, char * name);
void G_delete(Game * games, char * name);
void G_destroy(Game * games);

#endif
