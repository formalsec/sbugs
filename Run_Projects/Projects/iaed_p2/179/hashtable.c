#include "hashtable.h"

int hash(char *v, int M){
    unsigned long h, a = 31415, b = 27183;

    for(h = 0; *v != '\0'; v++, a= a*b%(M-1))
        h = (a*h + *v)%M;

    return h;
}


/* ------ Games hash table functions ------ */

Ht_games HTGinit(int max){
    Ht_games ht = malloc(sizeof(struct ht_games));
    int i;
    ht->num = 0;
    ht->size = 2*max;
    ht->games = malloc(ht->size*sizeof(Game));

    for(i = 0; i < ht->size; i++)
        ht->games[i] = NULLgame;
    
    return ht;
}

Ht_games HTinsertGame(Ht_games ht, Game game){
    unsigned long i = hash(game->name, ht->size);

    while(ht->games[i] != NULLgame)
        i = (i+1)%ht->size;
        
    ht->games[i] = game;
    
    if(ht->num++ >= ht->size/2)    /* Hash table is half full */
        ht = HTexpandGames(ht);
    
    return ht;
}

Game HTsearchGame(Ht_games ht, char *name){
    unsigned long i = hash(name, ht->size);
    
    while(ht->games[i] != NULLgame){
        if(strcmp(ht->games[i]->name, name) == 0)
            return ht->games[i];

        else
            i = (i+1)%ht->size;
    }

    return NULLgame;
}

void HTdeleteGame(Ht_games ht, char *name){
    Game aux, temp;
    unsigned long i = hash(name, ht->size);

    /* Searchs for the position of the game */
    while(ht->games[i] != NULLgame){
        if(strcmp(ht->games[i]->name, name) == 0)
            break;
        
        else
            i = (i+1)%ht->size;
    }

    if(ht->games[i] == NULLgame)
        return;

    aux = ht->games[i];
    ht->games[i] = NULLgame;
    freeGame(aux);
    ht->num--;

    /* Reinsert the games in front of the deleted one */
    for(i = (i+1)%ht->size; ht->games[i] != NULLgame; i = (i+1)%ht->size){temp = ht->games[i];
        ht->games[i] = NULLgame;
        ht = HTinsertGame(ht, temp);
        ht->num--;  /* Minus the same game */
    }

    temp = NULLgame;
}

Ht_games HTexpandGames(Ht_games ht){
    int i;
    Ht_games aux = ht, new_ht = HTGinit(2*ht->size); /* Double the initial size */
    
    /* Reinsert every game from ht to new_ht */
    for(i = 0; i < ht->size || new_ht->size == ht->size; i++){
        if(ht->games[i] != NULLgame)
            new_ht = HTinsertGame(new_ht, ht->games[i]);
    }
    
    free(aux->games);
    free(aux);
    aux = NULL;
    ht = NULL;
    return new_ht;
}

void freeHTGames(Ht_games ht){
    int i;

    for(i = 0; i < ht->size; i++){
        if(ht->games[i] != NULLgame)
            freeGame(ht->games[i]);
    }

    free(ht->games);
    ht->games = NULL;
    free(ht);
    ht = NULL;
}


/* ------ Teams hash table functions ------ */

Ht_teams HTTinit(int max){
    Ht_teams ht = malloc(sizeof(struct ht_teams));
    int i;
    ht->num = 0;
    ht->size = 2*max;
    ht->teams = malloc(ht->size*sizeof(Team));

    for(i = 0; i < ht->size; i++)
        ht->teams[i] = NULLteam;

    return ht;
}

Ht_teams HTinsertTeam(Ht_teams ht, Team team){
    unsigned long i = hash(team->name, ht->size);

    while(ht->teams[i] != NULLteam)
        i = (i+1)%ht->size;

    ht->teams[i] = team;
    
    if(ht->num++ >= ht->size/2)     /* Hash table is half full */
        ht = HTexpandTeams(ht);
    
    return ht;
}

Team HTsearchTeam(Ht_teams ht, char *name){
    unsigned long i = hash(name, ht->size);
    
    while(ht->teams[i] != NULLteam){
        if(strcmp(ht->teams[i]->name, name) == 0)
                return ht->teams[i];

        else
            i = (i+1)%ht->size;
    }

    return NULLteam;
}

Ht_teams HTexpandTeams(Ht_teams ht){
    int i;
    Ht_teams aux = ht, new_ht = HTTinit(2*ht->size); /* Double the initial size */
    
    /* Reinsert every game from ht to new_ht */
    for(i = 0; i < ht->size || new_ht->size == ht->size; i++){
        if(ht->teams[i] != NULLteam)
            new_ht = HTinsertTeam(new_ht, ht->teams[i]);
    }

    free(aux->teams);
    free(aux);
    aux = NULL;
    ht = NULL;
    return new_ht;
}

void freeHTTeams(Ht_teams ht){
    int i;

    for(i = 0; i < ht->size; i++){
        if(ht->teams[i] != NULLteam)
            freeTeam(ht->teams[i]);
    }

    free(ht->teams);
    ht->teams = NULL;
    free(ht);
    ht = NULL;
}
