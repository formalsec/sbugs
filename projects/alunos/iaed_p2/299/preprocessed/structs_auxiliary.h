#ifndef STRUCTS_AUXILIARY_H
#define STRUCTS_AUXILIARY_H

#include "structs.h"

/* Returns the end of a linked list of games */
games *new_game_at_end(games **list);

/* Returns the end of a linked list of teams */
teams *new_team_at_end(teams **list);

/* Creates the name (structure) of a new game,
 * and adds it to the linked list of names */
void new_name(char *name, game_names **name_list);

/* Eliminates the given game from the system */
void elim_game(games *game, games **head, game_names **names_pt);

/* Deletes a game's name */
void del_name(game_names *name, game_names **name_list);

/* Frees the memory allocated for a game and its name */
void free_game_pt(games *game, game_names **name_list);

#endif /* STRUCTS_AUXILIARY_H */
