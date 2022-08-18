#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "myLib.h"
#include "competition.h"
#include "game.h"

/* Creates a competition*/
Competition * comp_new(char * name) {

    extern char* strdup(const char*);

	Competition * competition = (Competition *) malloc(sizeof(Competition));
	EXIT_IF_ERROR("comp_new: create_competition");

	/* Inicializes variables*/
	competition->name  = strdup(name); 
	competition->count = 0;

	competition->first = NULL;
	competition->last  = NULL;

	return competition;
}

Comp_node * comp_new_node(Game *g) {
    Comp_node * cn = (Comp_node*) malloc(sizeof(Comp_node));
	EXIT_IF_ERROR("comp_new_node: malloc");
    cn->game = g;
    return cn;
}

/* frees memory allocated for comp_node */
void comp_node_free(Comp_node *cn) {
    ERROR_IF_NULL(cn, "comp_node_free", exit(EXIT_FAILURE));

    /* free do Game */
    game_free(cn->game);
    
    /* free do Comp_Node */
	free(cn);
}

/*frees memory allocated for competition struct*/
void competition_free(Competition *c) {
    Comp_node * cn;

    ERROR_IF_NULL(c, "competition_free", exit(EXIT_FAILURE));

    /* free name */
    free(c->name);
    
    cn = c->first;
    while(cn!=NULL) {
        Comp_node * next = cn->next;
        comp_node_free(cn);
        cn = next;
    }

    free(c);
}

void comp_add_game(Competition *c, Game *g) {

    Comp_node *cn;

    ERROR_IF_NULL(c, "comp_add_game", exit(EXIT_FAILURE));

    cn =  comp_new_node(g);
    cn->next = NULL;
    cn->previous = c->last;
    
    c->last = cn;

    /* Verification of first element */
    if (c->count==0) c->first = cn;

    c->count++;
}


/* Find a game in a node */
Comp_node * _comp_find_game(Competition *c,  char * game_name) {
	
    Comp_node *cn;

    ERROR_IF_NULL(c, "_comp_find_game", exit(EXIT_FAILURE));

	cn = c->first;
	while (cn!=NULL) {
		if ( strcmp(game_get_name(cn->game), game_name)==0 )
			return cn;
		cn = cn->next;
	}

	return NULL;
}


/*finds game using name */
Game * comp_find_game(Competition *c,  char * game_name) {
   Comp_node * cn;

    cn= _comp_find_game(c, game_name);
    if (cn==NULL)
        return NULL;
    else
        return cn->game;
}

/*removes game from competition*/
int comp_remove_game(Competition *c, char * game_name) {
    
    Comp_node *cn;

    ERROR_IF_NULL(c, "competition_remove_game", exit(EXIT_FAILURE));

    cn = _comp_find_game(c,game_name);
	if (cn==NULL)
		return -1;
	
	c->count--;

    /* If is the first */
	if (cn->previous==NULL) {
		c->first = cn->next;
	}

	/* If is the last */
	if (cn->next==NULL) {
		c->last = cn->previous;
	}

	/* If is not the first */
	if (cn->previous!=NULL) {
		cn->previous->next = cn->next;
	}

    comp_node_free(cn);
	return 0;
}

/* Set new score for the game */
Game * comp_set_score(Competition *c, char * game_name, int s1, int s2) {
    Comp_node *cn;

    ERROR_IF_NULL(c, "comp_set_score", exit(EXIT_FAILURE));

    cn = _comp_find_game(c, game_name);
	if (cn==NULL)
		return NULL;
    else {
        game_set_score(cn->game, s1, s2);
        return cn->game;
    }
}

/* Competition with more victories */
int comp_get_victories(Competition *c, char * team_name){

    Comp_node *cn;
    int victories = 0;
    Team * team;

    ERROR_IF_NULL(c, "comp_get_victories", exit(EXIT_FAILURE));

    cn = c->first;
    while( cn!=NULL ) {

        team = game_get_team(cn->game, team_name);

        if ( team!=NULL && game_get_winner(cn->game)==team )
            victories++;

        cn = cn->next;
    }

    return victories;
}

/* Competition prints internal struct */
void competition_print(Competition *c) {

    char first_game[100];
    char last_game[100];

    ERROR_IF_NULL(c, "competition_print", exit(EXIT_FAILURE));


    if (c->first!=NULL)
        strcpy(first_game, c->first->game->name);
    else
        strcpy(first_game,"NULL");
    

   if (c->last!=NULL)
        strcpy(last_game, c->last->game->name);
    else
        strcpy(last_game, "NULL");


    printf("COMP: %s, %d, %s, %s\n", c->name, c->count, first_game, last_game);
}

/* Competition prints games within */
void comp_print_games(Competition *c, int nl) {

    Comp_node *cn;
    char buf[GAME_MAX_NAME+2*TEAM_MAX_NAME+10];

    ERROR_IF_NULL(c, "competition_print", exit(EXIT_FAILURE));

    cn = c->first;
    while (cn!=NULL) {
        printf("%d %s\n", nl, game_to_string(cn->game, buf));
        cn  = cn->next;
    }
}