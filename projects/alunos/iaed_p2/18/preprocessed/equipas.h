#ifndef EQUIPAS_C
#define  EQUIPAS_C

typedef struct team{
  char *name;
  int victories;
}Team;

typedef struct teams{
  Team team;
  struct teams *nextTeam;
}Teams;

Team createTeam(char *name);
int isTeam(char *name, Team team);
void addVictory(Teams *teamsList, char *team);
void removeVictory(Teams *teamsList, char *team);
void freeTeam(Team team);

Teams *createTeams(char *name);
int addTeam(char * name, Teams *teamsList);
Team searchTeam(Teams *teamsList, char* name);
void printTeam(Teams *teamsList, char *teamName, int commandNumber);
void printBest(Teams *teamsList, int commandNumber);
void freeTeams(Teams *teamsList);

#endif
