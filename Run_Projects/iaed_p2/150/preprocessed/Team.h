#ifndef _TEAM_
#define _TEAM_


/**** structure *****/

typedef struct Team {
    char *name;
    int wins;
}Team;


/****** prototypes ******/

/* Creates a new team and returns the team's pointer. */
Team * newTeam(char * str);

/* Prints a team */
void printTeam(Team * team);

/* Frees all memory attached to a team. */
void destroyTeam(Team * team);


#endif