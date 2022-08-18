#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "structs.h"
#include "hash.h"

Team teamHashLookup(Team* hash_team_sys, char* name) {

    int i;

    i = hash(name, HASH_TABLE_LIM);

    while (hash_team_sys[i]) {

        if (!strcmp(hash_team_sys[i]->name, name)) {

            return hash_team_sys[i];
        }
        else i = (i + 1) % HASH_TABLE_LIM;
    }
    return NULL;
}

Game gameHashLookup(Game* hash_game_sys, char* name) {

    int i;

    i = hash(name, HASH_TABLE_LIM);

    while (hash_game_sys[i]) {

        if (!strcmp(hash_game_sys[i]->name, name) &&
        !ghost(hash_game_sys[i])) {

            return hash_game_sys[i];
        }
        else i = (i + 1) % HASH_TABLE_LIM;
    }
    return NULL;
}

Team createTeam(char* name) {

    Team new_team = (Team)malloc(sizeof(struct team));
    new_team->name = (char*)malloc(sizeof(char)*(strlen(name)+1));

    strcpy(new_team->name, name);
    new_team->wins = 0;

    return new_team;
}

Game createGame(char* game_name, char* t1_name, char* t2_name,
unsigned int t1_score, unsigned int t2_score, int nl_count) {

    Game new_game =
    (Game)malloc(sizeof(struct game));
    new_game->name =
    (char*)malloc(sizeof(char)*(strlen(game_name) + 1));
    new_game->team1 =
    (char*)malloc(sizeof(char)*(strlen(t1_name) + 1));
    new_game->team2 =
    (char*)malloc(sizeof(char)*(strlen(t2_name) + 1));

    strcpy(new_game->name, game_name);
    strcpy(new_game->team1, t1_name);
    strcpy(new_game->team2, t2_name);
    new_game->t1_score = t1_score;
    new_game->t2_score = t2_score;
    new_game->n_line = nl_count;
    new_game->removed_state = FALSE;

    return new_game;
}

void insertTeam(Team* hash_team_sys, Team t_dummy) {

    int i = hash(t_dummy->name, HASH_TABLE_LIM);

    while (hash_team_sys[i] != NULL) i = (i + 1) % HASH_TABLE_LIM;
    hash_team_sys[i] = t_dummy;
}

void insertGame(Game* hash_game_sys, Game g_dummy) {

    int i = hash(g_dummy->name, HASH_TABLE_LIM);

    while (hash_game_sys[i] != NULL) i = (i + 1) % HASH_TABLE_LIM;
    hash_game_sys[i] = g_dummy;
}

unsigned int bestTeamsScoreLookup(Team* hash_team_sys) {

    int i;
    unsigned int max = 0;

    for (i = 0; i < HASH_TABLE_LIM; i++) {

        if (hash_team_sys[i] && hash_team_sys[i]->wins > max)
            max = hash_team_sys[i]->wins;
    }
    return max;
}

void* hashStartup() {

    Team* temp = calloc(HASH_TABLE_LIM, sizeof(void*));
    return temp;

}

void hashShutdown(Team* hash_team_sys, Game* hash_game_sys) {

    int i;

    for (i = 0; i < HASH_TABLE_LIM; i++) {

        if (hash_team_sys[i] != NULL) {

            free(hash_team_sys[i]->name);
            free(hash_team_sys[i]);
        }
        if (hash_game_sys[i] != NULL) {

            free(hash_game_sys[i]->name);
            free(hash_game_sys[i]->team1);
            free(hash_game_sys[i]->team2);
            free(hash_game_sys[i]);
        }
    }

    free(hash_team_sys);
    free(hash_game_sys);
}

int gameCmpNLine(const void* p1, const void* p2) {

    const Game g1 = *(Game*)p1;
    const Game g2 = *(Game*)p2;

    return (g1->n_line - g2->n_line);
}

int teamCmpABC(const void* p1, const void* p2) {

    const Team t1 = *(Team*)p1;
    const Team t2 = *(Team*)p2;

    return strcmp(t1->name, t2->name);
}