#ifndef COMMANDS
#define  COMMANDS
#include "Teams.h"
#include "Games.h"

typedef struct System{
	TS     	  *ts;
	GS        *gs;
	int inputline;
}System;

/* allocates the memmory needed for the System */
void Start_Sytem(System *s);

/* adds a new game to the System */
void command_add_game(System *s);

/* prints all the games in the System in input order */
void command_list_game(System *s);

/* finds and prints an existing game */
void search_game(System *s);

/* removes a game from the hash table and the double linked list */
void remove_game(char *buffer, System *s);

/* deleates a specific game from the System */
void deleate_game(System *s);

/* changes the score aof a spefic game */
void change_score(System *s);

/* inserts a team in the System when possible */
void command_add_team(System *s);

/* finds and prints an existing team */
void command_search_team(System *s);

/* finds and prints the biggest winners */
void command_bggst_wnnrs(System *s);

/* Frees all the remaining allocated memmory in the system */
void Stop_System(System *s);

#endif