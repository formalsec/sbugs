#ifndef __GAMES_H__
#define __GAMES_H__

typedef struct {
    char * name;
    int wins;
} Team; /* Internal representation of a team */

typedef struct {
    char *name;
    Team *home, *away;
    unsigned int homeScore, awayScore;
} Game; /* Internal representation of a game */

typedef Game *item;


char *readName();

void addGame(int count);
void addTeam(int count);
void listGames();
void searchGame(int count);
void searchTeam(int count);
void deleteGame(int count);
void changeScore(int count);
void mostSuccessfulTeams(int count);
void clean();
void printNames(char **arr, int len, int count);
void freeGame(void *game);
void freeTeam(void *team);
char *getName(Game *game);
void printGame(int count, Game *game);
void mergeSort(char **arr, char **aux, int l, int r);
void merge(char **arr, char **aux, int left, int m, int right);
int lower(const char *a, const char *b);
int amountOfWins(void *team);
char *nameOfTeam(void *team);
#endif