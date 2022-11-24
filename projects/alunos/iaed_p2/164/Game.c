#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include "Game.h"

/* Creates and returns a new Game, initializing all it's values to 0 and NULL.*/
Game InitGame(){
    Game g = (Game) can_fail_malloc(sizeof(struct game));
    SetScore(0, 0, g);
    g->team_1 = NULL;
    g->team_2 = NULL;
    g->name = NULL;
    return g;
}

/* Receives a Game and 2 scores, setting the Game's scores as "score_1":"score_2".*/
void SetScore(int score_1, int score_2, Game g){
    g->score_1 = score_1;
    g->score_2 = score_2;
}

/* Receives a Game and a name, setting the Game's name as "name", only allocating the necessary memory.*/
void SetName(char name[],Game g){
    char * p_name;
    p_name = (char*) can_fail_malloc(strlen(name) + 1);
    strcpy(p_name, name);
    g->name = p_name;
}

/* Receives a Game and 2 Teams, setting the Game's Teams as "team_1" and "team_2".*/
void SetTeams(Team team_1, Team team_2, Game g){
    g->team_1 = team_1;
    g->team_2 = team_2;
}

/* Receives a Game and returns the winner Team.*/
Team Winner(Game g){
    if (GameScore1(g) > GameScore2(g))
        return GameTeam1(g);
    else if (GameScore1(g) < GameScore2(g))
        return GameTeam2(g);
    else 
        return NULL;
}

/* Receives a Game and returns it's name.*/
char * GameName(Game g){
    return g->name;
}

/* Receives a Game and returns it's "team_1".*/
Team GameTeam1(Game g){
    return g->team_1;
}

/* Receives a Game and returns it's "team_2".*/
Team GameTeam2(Game g){
    return g->team_2;
}

/* Receives a Game and returns it's "score_1".*/
int GameScore1(Game g){
    return g->score_1;
}

/* Receives a Game and returns it's "score_2".*/
int GameScore2(Game g){
    return g->score_2;
}

/* Receives a Game and a line number "NL", writing the line number and the Game's characteristics.*/
void WriteGame(Game g, int NL){
    printf("%d %s %s %s %d %d\n", NL, GameName(g), TeamName(GameTeam1(g)), TeamName(GameTeam2(g)), GameScore1(g), GameScore2(g));
}

/* Receives a Game and destroys it, aswell as it's name.*/
void DestroyGame(Game g){
    free(GameName(g));
    free(g);
}