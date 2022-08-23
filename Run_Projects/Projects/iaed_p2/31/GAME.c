#include "GAME.h"


/* Auxiliar functions of games. */

/* Creates a system of game. */
Game ** init_game(Game ** game_hash){
     int i = 0;

    game_hash = malloc(sizeof(Game*) * HASH_SIZE);

    for(; i < HASH_SIZE; i++)
        game_hash[i] = NULL;

    return game_hash;

}


/* Creates a new game. */
Game * create_game(char * name_game, team * teamA, team * teamB, int scoreA, int scoreB){
    Game* game = malloc(sizeof(Game));
    
    game->name = malloc(sizeof(char) * (strlen(name_game)+1));
    game->A = teamA;
    game->B = teamB;
    game->next = NULL;

    strcpy(game->name, name_game);
    game->scoreA = scoreA;
    game->scoreB = scoreB;

    return game;
}



/* Inserts the game at the beginning of the list of games. */
Game * push_game(char * name_game, team * A, team * B, int sA, int sB, Game * last){
    Game * first = create_game(name_game, A, B, sA, sB);
    first->next = last;

    return first;

}


/* Removes the first element of the Game list and returns the new head. */
Game * pop_game(Game * head){
    Game * next;
    
    if(!head) 
        return NULL;
    
    next = head ->next;

    free(head->name);
    free(head);

    return next;
}

   
/* Destroys the games index/list of game. */
Game * destroy_game(Game * game_hash){
    while(game_hash){
        game_hash = pop_game(game_hash);
    }

    return NULL;
}


/* Frees all memory associated with the games system. */
Game ** destroy_full_game(Game ** game_hash){
    int i;
    for(i = 0; i < HASH_SIZE; i++){
        game_hash[i] = destroy_game(game_hash[i]);   
    }
    free(game_hash);

    return NULL;
}

/* Adds a game in games list by the order of NL. */
Game * add_order_game(Game * order_team, char * name, team * A, team * B,int sA, int sB, int nl_g){
    Game * new = order_team, *aux = order_team;

    if(!new){
        new = create_game(name,A,B,sA,sB);
        new->NL = nl_g;

        return new;
    } 

    /* If the new game has low NL than the list.
    new game becomes the first on the list. */
    if( nl_g < new->NL){
        new = push_game( name, A, B, sA, sB, new);
        new->NL = nl_g;

        return new;
    }

    new = new-> next;

    for(; new; new = new->next,aux = aux->next){
        if(nl_g < new->NL){
            new = push_game(name, A, B, sA, sB, new);
            new->NL = nl_g;
            aux->next = new;

            return order_team;
        }
    }
    
    aux->next = create_game(name, A, B, sA, sB);
    aux->next->NL = nl_g;
    
    return order_team;
}


