#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "myLib.h"
#include "team.h"
#include "game.h"
#include "teams.h"
#include "competition.h"

#define BUFFER_SIZE 100

/*Inicialization of global variables*/
int NL = 0;
Teams * teams;
Competition * c;

/*Readline*/
void read_line(char* buf) {
	int i;
	fgets(buf, BUFFER_SIZE, stdin);
	for(i=0; i<BUFFER_SIZE && buf[i]!=0; i++) {
		if (buf[i]==':') 
            buf[i]=' ';
	}
     NL++;
}


/* Adds new game */
void command_a() {
	char buf	[BUFFER_SIZE];
	char nameG 	[GAME_MAX_NAME];
	char nameT1	[TEAM_MAX_NAME];
	char nameT2	[TEAM_MAX_NAME];
	int  score1, score2;
	
    Game *game; 
    Score score;
    Team *t1;
	Team *t2;

	/* Read line: name,team1,team2,score1,score2 */
	read_line(buf);

	/* Parse parameters: name,team1,team2,score1,score2*/
	sscanf(buf, "%s%s%s%d%d", nameG, nameT1, nameT2, &score1, &score2);
	
    /* Verification of a game with the game_name */
    if ( comp_find_game(c, nameG)!=NULL ) {
        printf("%d Jogo existente.\n", NL);
        return;
    }

    /* Verification of creation of t1 && t2 */
    t1 = teams_get_team(teams, nameT1);
    t2 = teams_get_team(teams, nameT2);
    if( t1==NULL || t2==NULL) {
		printf("%d Equipa inexistente.\n", NL);
		return; 
	}

    score.t1 = score1;
    score.t2 = score2;

    game = new_game(nameG, t1, t2, score);

    comp_add_game(c, game);
}

/* Adds new team */
void command_A() {                                

	char buf[BUFFER_SIZE];
	char name[TEAM_MAX_NAME];
	Team *t;

	/* Read line: name */
	read_line(buf);

	/* Parse parameters: name*/
	sscanf(buf, "%s", name);

    /* Verification of an existing team with name: `name` */
    if ( teams_get_team(teams, name)!=NULL ) {
        printf("%d Equipa existente.\n", NL);
        return;
    }

    /* Creation of team and adding it too colection of teams */
	t = team_new(name);                                           
    teams_add(teams, t);
}

/* List games by the introduzed order */
void command_l() {
	char buf[BUFFER_SIZE];

	/* Read line: name */
	read_line(buf);


    comp_print_games(c, NL);

}

/* Searches game by name*/
void command_p() {
	char buf[BUFFER_SIZE];
	char name[GAME_MAX_NAME];
	Game *g;

	/* Read line: name */
	read_line(buf);

	/* Parse parameters: name*/
	sscanf(buf, "%s", name);


    /* Verification of a game with the name: `nameG` */
    g = comp_find_game(c, name);
    if ( g==NULL ) {
        printf("%d Jogo inexistente.\n", NL);
        return;
    }

    /*Resulte: NL nome-jogo nome-equipa1 nome-equipa2 score1 score2 */
    printf("%d %s %s %s %d %d\n", NL, game_get_name(g), g->t1->name, g->t2->name, game_get_score1(g), game_get_score2(g));

}

/*Searches team by name*/
void command_P() {
	char buf[BUFFER_SIZE];
	char name[TEAM_MAX_NAME];
	Team *t;

	/* Read line: name*/
	read_line(buf);

	/* Parse parameters: name*/
	sscanf(buf, "%s", name);

    t = teams_get_team(teams, name);

    /*Verification if the team exists or not*/
	if(t==NULL) {
		printf("%d Equipa inexistente.\n", NL);
        return;
	}

    printf("%d %s %d\n", NL, name, comp_get_victories(c, name));
}

/* Deletes game */
void command_r() {
    char buf[BUFFER_SIZE];
	char name[GAME_MAX_NAME];
	Game *g;

	/* Read line: name */
	read_line(buf);

	/* Parse parameters: name*/
	sscanf(buf, "%s", name);


    /* Verification of game with name:`nameG` */
    g = comp_find_game(c, name);
    if ( g==NULL ) {
        printf("%d Jogo inexistente.\n", NL);
        return;
    }

    comp_remove_game(c, name);
}

/* Changes score of a game */
void command_s() {
    char buf[BUFFER_SIZE];
	char name[GAME_MAX_NAME];
    int  score1, score2;

	Game *g;

	/* Read line: name */
	read_line(buf);

	/* Parse parameters: name*/
	sscanf(buf, "%s%d%d", name, &score1, &score2);

    /* Verification of game with name: `name` */
    g = comp_find_game(c, name);
    if ( g==NULL ) {
        printf("%d Jogo inexistente.\n", NL);
        return;
    }

    comp_set_score(c, name, score1, score2);
}

/* Finds teams that won more games */
void command_g() {

    char buf[BUFFER_SIZE];
    /*Team ** equipas;
    int  * victorias;
    int  i;
    int max_victorias;*/

	/* Read line: name */
	read_line(buf); 
    
    /*equipas   = teams_get_all(teams);*/
    /*victorias = malloc(teams->count*size_t(int));*/

    /* sort equipas utilizando equipas[i]->name */
   
   /* for (i=0; i<teams->count; i++)
        victorias[i] = comp_get_victories(c, equipas[i]);*/

    /* calcula o maximo no array victorias */
    /*max_victorias = 20;*/

    /* Imprimir aqueles que tem o maximo 

   free(victorias);
   free(equipas); */
   return;
}


int main() {
    char command;
    teams = teams_new();
    c = comp_new("Liga NOS");

	do {
		command=getchar();
		switch(command)
		{
			case 'a': /* Adds new game */
				command_a();
				break;

			case 'A': /* Adds new team */
				command_A();
                break;

			case 'l': /* List games by the introduzed order */
				command_l();
                break;

			case 'p': /* Searches game by name*/
				command_p();
                break;

            case 'P': /* Searches team by name*/
				command_P();
                break;

			case 'r': /* Deletes game */
				command_r();
                break;

			case 's': /* Changes score of a game */
				command_s(); 
				break;

			case 'g': /* Finds teams that won more games */
				command_g();
				break;

			case 'x': break;
		}

	} while(command!='x');


	return EXIT_SUCCESS;
}
