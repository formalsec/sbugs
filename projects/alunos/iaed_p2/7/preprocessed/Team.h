#include "constants.h" /*  */

#ifndef TEAM_H
#define TEAM_H

/* Key for Team Structure. */
typedef const char* t_Key;

/* Team Structure. */
typedef struct team {
    char *name;
	uint matches_won;
}* Team;

#define t_key(T) (T->name)
#define t_eq(T1, T2) (strcmp(T1, T2) == 0)
#define t_cmp(T1, T2) (strcmp(T1, T2))

/* Returns a new team with the given name. */
Team new_team(const char *team_name);

/* Frees given team. */
void free_team(Team t);

#endif /* TEAM_H */

