#ifndef __TEAMS__
#define __TEAMS__

/* struct that models a team*/
typedef struct team{
    char *name;
    int number_of_wins;
} team;

/*node of a list of teams, is stored in the hastable*/
typedef struct team_node{
    struct team_node *next;
    team *tptr;
} team_node;

int hash(char *string);
char* myStrdup(char *string);
team_node** makeHashTeams();
team* searchHashTeams(team_node **hastable, char *name);
void freeAllMemoryTeams(team_node**);
void addTeam(team_node** hashtable, int line);
void searchTeam(team_node** hashtable, int line);
void findChampions(team_node** hashtable, int line);

#endif
