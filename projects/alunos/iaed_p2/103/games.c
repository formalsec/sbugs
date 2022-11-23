#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "games.h"
#include "teams.h"

#define MAX_NAME        1024
#define HASH_TABLE_SIZE 1061

/* creates new empty list of games */
list_games* makeListGames(){
    list_games *new_list = (list_games*) can_fail_malloc(sizeof(list_games));
    new_list->head = NULL;
    new_list->last = NULL;
    return new_list;
}

/*searches a list of games for a game with a matching name*/
game *searchListGames(list_games *list, char *name){
    game_node *t = list->head; 
    while (t){
        if (!strcmp(t->gameptr->name, name)){
            return t->gameptr;
        }
        t = t->next;
    }
    return NULL;
}

/* adds game g as the last element of the list */
void addLast(list_games *l, game *g){
    game_node *new_last = (game_node*) can_fail_malloc(sizeof(game_node));
    new_last->gameptr = g;
    new_last->next = NULL;
    new_last->previous = l->last;
    if (!(l->head)){ /*if list is empty*/
        l->head = new_last;
        l->last = new_last;
        return;
    }
    l->last->next = new_last;
    l->last = new_last;
}

/*removes an element from a list*/
void removeFromList(list_games *list, char *name){
    game_node *t;
    for (t = list->head; t; t = t->next){
        if (!strcmp(t->gameptr->name, name)){
            if (t == list->head){
                list->head = t->next;
                if (t->next != NULL){
                    t->next->previous = NULL;
                }
            }
            else if (t == list->last){
                list->last = t->previous;
                if (t->previous != NULL){
                    t->previous->next = NULL;
                }
            }
            else{
                t->previous->next = t->next;
                t->next->previous = t->previous;
            }
            free(t);
            break;
        }
    }
}

/*initializes the hashtable of games*/
list_games** makeHashGames(){
    list_games **hash_table = (list_games**) can_fail_malloc(sizeof(list_games*) * HASH_TABLE_SIZE);
    int i;
    for (i = 0; i < HASH_TABLE_SIZE; i++){
        hash_table[i] = makeListGames();
    }
    return hash_table;
}

/*searches for a game in the hastable*/
game* searchHashGames(list_games **hastable, char *name){
    int i = hash(name);
    return searchListGames(hastable[i], name);
}

/*inserts a game in the hashtable*/
void insertGame(list_games **hashtable, game *g){
    int i = hash(g->name);
    addLast(hashtable[i], g);
}

/*frees all the memory associated with a game*/
void freeGame(game *g){
    free(g->name);
    free(g->team1);
    free(g->team2);
    free(g);
}

/*frees all memory associated with a list of games*/
void freeList(list_games *lgptr){
    game_node *t = lgptr->head;
    while (t){
        game_node *old = t;
        freeGame(t->gameptr);
        t = t->next;
        free(old);
    }
    free(lgptr);
}

/*frees all memory associated with the games*/
void freeAllMemoryGames(list_games *lgptr, list_games **hashgames){
    int i;
    freeList(lgptr);
    for (i = 0; i < HASH_TABLE_SIZE; i++){
        list_games *t = hashgames[i];
        game_node *g = t->head;
        while (g){
            game_node *old = g;
            g = g->next;
            free(old);
        }
        free(t);
    }
    free(hashgames);
}

/*initializes a game*/
void initGame(game *new_game, char *match_name, char *team1, char *team2, int score1, int score2){
    new_game->name = myStrdup(match_name);
    new_game->team1 = myStrdup(team1);
    new_game->team2 = myStrdup(team2);
    new_game->score_team1 = score1;
    new_game->score_team2 = score2;
}

/* adds a new game to the system */
void addGame(list_games *lgptr, list_games **hashgames, team_node **hasteams, int line){
    char *match_name_buffer = (char*) can_fail_malloc(sizeof(char) * MAX_NAME);
    char *team1_buffer = (char*) can_fail_malloc(sizeof(char) * MAX_NAME);
    char *team2_buffer = (char*) can_fail_malloc(sizeof(char) * MAX_NAME);
    int score1, score2;
    game *new_game;
    scanf(" %[^:\n]:%[^:\n]:%[^:\n]:%d:%d", match_name_buffer, team1_buffer, team2_buffer, &score1, &score2);
    if (searchHashGames(hashgames, match_name_buffer)){
        printf("%d Jogo existente.\n", line);
        free(match_name_buffer);
        free(team1_buffer);
        free(team2_buffer);
        return;
    }
    else if (!searchHashTeams(hasteams, team1_buffer) || !searchHashTeams(hasteams, team2_buffer)){
        printf("%d Equipa inexistente.\n", line);
        free(match_name_buffer);
        free(team1_buffer);
        free(team2_buffer);
        return;
    }
    new_game = (game*) can_fail_malloc(sizeof(game));
    initGame(new_game, match_name_buffer, team1_buffer, team2_buffer, score1, score2);
    insertGame(hashgames, new_game);
    addLast(lgptr, new_game);
    if (score1 > score2){
        searchHashTeams(hasteams, team1_buffer)->number_of_wins++;
    }
    else if (score1 < score2){
        searchHashTeams(hasteams, team2_buffer)->number_of_wins++;
    }
    free(match_name_buffer);
    free(team1_buffer);
    free(team2_buffer);
}

/* prints out the data of all matches based on the order they were added to the system*/
void listGames(list_games *lgptr, int line){
    game_node *t; 
    for (t = lgptr->head; t; t = t->next){
        printf("%d %s %s %s %d %d\n",
        line,
        t->gameptr->name,
        t->gameptr->team1,
        t->gameptr->team2,
        t->gameptr->score_team1,
        t->gameptr->score_team2);
    }
}

/*searches for a game and prints its data*/
void searchGame(list_games **hastable, int line){
    char *name = (char*) can_fail_malloc(sizeof(char) * MAX_NAME);
    game *g;
    scanf(" %[^:\n]", name);
    g = searchHashGames(hastable, name);
    if (!g){
        printf("%d Jogo inexistente.\n", line);
        free(name);
        return;
    }
    printf("%d %s %s %s %d %d\n",
    line,
    g->name,
    g->team1,
    g->team2,
    g->score_team1,
    g->score_team2);
    free(name);
}

/*removes a game from the system*/
void deleteGame(list_games *lgprt, list_games **hashgames, team_node **hashteams, int line){
    char *name = (char*) can_fail_malloc(sizeof(char) * MAX_NAME);
    game *g;
    scanf(" %[^:\n]", name);
    g = searchHashGames(hashgames, name);
    if (!g){
        printf("%d Jogo inexistente.\n", line);
        free(name);
        return;
    }
    if (g->score_team1 > g->score_team2){
        searchHashTeams(hashteams, g->team1)->number_of_wins--;
    }
    else if (g->score_team1 < g->score_team2){
        searchHashTeams(hashteams, g->team2)->number_of_wins--;
    }
    removeFromList(lgprt, name);
    removeFromList(hashgames[hash(name)], name);
    freeGame(g);
    free(name);
}

/*change the score of a game in the system, and adjusts the victories of each team accordingly*/
void changeScore(list_games **hashgames, team_node** hashteams, int line){
    char *name = (char*) can_fail_malloc(sizeof(char) * MAX_NAME);
    int old_score1, old_score2, new_score1, new_score2;
    game *g;
    scanf(" %[^:\n]:%d:%d", name, &new_score1, &new_score2);
    g = searchHashGames(hashgames, name);
    if (!g){
        printf("%d Jogo inexistente.\n", line);
        free(name);
        return;
    }
    old_score1 = g->score_team1;
    old_score2 = g->score_team2;
    if (old_score1 > old_score2){
        if (new_score1 < new_score2){
            searchHashTeams(hashteams, g->team1)->number_of_wins--;
            searchHashTeams(hashteams, g->team2)->number_of_wins++;
        }
        else if (new_score1 == new_score2){
            searchHashTeams(hashteams, g->team1)->number_of_wins--;
        }
    }
    else if (old_score2 > old_score1){
        if (new_score2 < new_score1){
            searchHashTeams(hashteams, g->team2)->number_of_wins--;
            searchHashTeams(hashteams, g->team1)->number_of_wins++;
        }
        else if (new_score2 == new_score1){
            searchHashTeams(hashteams, g->team2)->number_of_wins--;
        }
    }
    else{
        if (new_score1 > new_score2){
            searchHashTeams(hashteams, g->team1)->number_of_wins++;
        }
        else if (new_score2 > new_score1){
            searchHashTeams(hashteams, g->team2)->number_of_wins++;
        }
    }
    g->score_team1 = new_score1;
    g->score_team2 = new_score2;
    free(name);
}
