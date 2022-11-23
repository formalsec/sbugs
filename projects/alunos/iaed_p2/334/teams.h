#ifndef TEAMS_H__
#define TEAMS_H__

typedef struct teamList_ teamList;
typedef struct gameList_ gameList;

struct teamList_
{
    char *name;
    int won;
    teamList *next;
};

struct gameList_
{
    char *name;
    teamList *team1;
    teamList *team2;
    int score1;
    int score2;
    gameList *next;
    gameList *prev;
};

teamList *addTeam(teamList *t, char *name);
gameList *addGame(gameList *g, char *name, teamList *team1, teamList *team2, int score1, int score2);

teamList *findTeam(teamList *t, char *name);
gameList *findGame(gameList *g, char *name);

gameList *deleteGame(gameList *g, gameList *game);

void freeTeams(teamList *t);
void freeGames(gameList *t);


#endif /* TEAMS_H__ */
