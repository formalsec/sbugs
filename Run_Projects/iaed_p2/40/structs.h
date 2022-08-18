#ifndef OURSTRUCTS
#define OURSTRUCTS

#define HASH_TABLE_LIM 100000
#define HASH_ELM_LIM 90000
#define STRINGLIM 1024
#define TRUE 1
#define FALSE 0

#define ghost(a) (a->removed_state == TRUE)

typedef struct team {
    char* name;
    unsigned int wins;
}* Team;

typedef struct game {
    char *name, *team1, *team2;
    unsigned int t1_score, t2_score;
    int n_line;
    int removed_state;
}* Game;

Team teamHashLookup(Team*, char*);
Game gameHashLookup(Game*, char*);
Team createTeam(char*);
Game createGame(char*, char*, char*, unsigned int, unsigned int, int);
void insertTeam(Team*, Team);
void insertGame(Game*, Game);
unsigned int bestTeamsScoreLookup(Team*);

void* hashStartup();
void hashShutdown(Team*, Game*);

int gameCmpNLine(const void*, const void*);
int teamCmpABC(const void*, const void*);

#endif