#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "consts.h"
#include "structures.h"

/*all the team structure methods; src = teams.c */
team *newTeam(char team_name[]);
void insertTeam(team *hash_table[], team *new_team);
team *findTeam(team *hash_table[], char *name);
void initTeamHashTable(team *hash_table[]);
void freeTeamHashTable(team *hash_table[]);
/*all the game structure methods; src = games.c */
game *newGame(char *name, char *team_name1, char *team_name2, int score1, int score2);
void insertGame(game *hash_table[], game *new_game);
game *findGame(game *hash_table[], char *name);
void deleteGame(game *hash_table[], char *name);
void initGameHashTable(game *hash_table[]);
void printSingleGame(game *single_game, int NL);
void freeGameHashTable(game *hash_table[]);
/*all the game_reference structure methods; src = game_ref.c */
game_reference *newReference(game *data);
game_reference *findReference(game_reference *head, char *name);
void pushReference(game_reference **head, game_reference *new_game);
void deleteReference(game_reference **head, game_reference *node_to_delete);
void printReference(game_reference *head, int  NL);
void freeReference(game_reference *head);
/* prints best teams; src = print_best_teams.c */
void printBestTeams(team *team_hash_table[], int NL);

/*
main function
*/
int main(){	
	/* input definition */
	char input[MAX_INPUT];
	/* strings definition */
	char *command, *name, *team_name1, *team_name2;
	/* game hash table definition */
	game *game_hash_table[TABLE_SIZE], *game_current;
	/* reference linked list of games definition */
	game_reference *game_head;
	/* teams definition */
	team *team_hash_table[TABLE_SIZE], *team1, *team2;
	/* ints definition */
	int score1, score2, NL;
	/* actual initialization */
	initGameHashTable(game_hash_table);
	initTeamHashTable(team_hash_table);
	NL = 0;
	game_head = NULL;
	team1 = NULL;
	team2 = NULL;
	game_current = NULL;
	command = can_fail_malloc(sizeof(char));
	team_name1 = can_fail_malloc(MAX_NAME*(sizeof(char)));
	team_name2 = can_fail_malloc(MAX_NAME*(sizeof(char)));
	name = can_fail_malloc(MAX_NAME*(sizeof(char)));
	/* main loop, terminates after the <x> command */
	for(;;){
		/* getting input */
		fgets(input, MAX_INPUT, stdin);
		/* parsing input */
		sscanf(input, "%1c %[^:\n]:%[^:\n]:%[^:\n]:%d:%d",
		 command, name, team_name1, team_name2, &score1, &score2);
		++NL;
		/* switch decides what case to execute regarding to the command */
		switch(command[0]){
			case 'a':; /* <a> command */
				/* creates new game */
				game_current = newGame(name, team_name1, team_name2, score1, score2);
				/* 
					teams initialization not only to handle bad input,
					but also to handle wins
				 */
				team1 = findTeam(team_hash_table, team_name1);
				team2 = findTeam(team_hash_table, team_name2);
				/* handling bad input */
				if(findGame(game_hash_table, game_current->name)!=NULL) printf("%d Jogo existente.\n", NL);
				else if(team1==NULL ||
					team2==NULL){
					printf("%d Equipa inexistente.\n", NL);
				}
				else{
					/* handling wins */
					if(score1 > score2) team1->wins++;
					else if(score2 > score1) team2->wins++;
					/* inserting to the game hash table */
					insertGame(game_hash_table, game_current);
					/* pushing to the reference list */
					pushReference(&game_head, newReference(game_current));
				}
				break;
			case 'A':;
				/* handling bad input */
				if(findTeam(team_hash_table, name)!=NULL){
					printf("%d Equipa existente.\n", NL);
				}/* inserting to the team hash table */
				else insertTeam(team_hash_table, newTeam(name));
				break;
			case 'l':;
				/* printing all the games */
				printReference(game_head, NL);
				break;
			case 'p':;
				/* finding the game */
				game_current = findGame(game_hash_table, name);
				/* handling bad input */
				if(game_current==NULL) printf("%d Jogo inexistente.\n", NL);
				else printSingleGame(game_current, NL); /* printing the game */
				break;
			case 'P':;
				/* finding the team */
				team1 = findTeam(team_hash_table, name);
				/* handling bad input */
				if(team1==NULL){
					printf("%d Equipa inexistente.\n", NL);
				}else{
					/* printing the team */
					printf("%d %s %d\n", NL, name, team1->wins);
				}
				break;
			case 's':;
				sscanf(input, "s %[^:\n]:%d:%d", name, &score1, &score2);
				/* finding the game */
				game_current = findGame(game_hash_table, name);
				/* handling bad input */
				if(game_current == NULL) printf("%d Jogo inexistente.\n", NL);
				else{
					/* finding the teams */
					team1 = findTeam(team_hash_table, game_current->team1);
					team2 = findTeam(team_hash_table, game_current->team2);
					/* handling wins */
					if(score1>score2 && *game_current->score1 < *game_current->score2) team1->wins++;
					if(score1<score2 && *game_current->score1 > *game_current->score2) team1->wins--;
					if(score1>score2 && *game_current->score1 == *game_current->score2) team1->wins++;
					if(score1==score2 && *game_current->score1 > *game_current->score2) team1->wins--;
					if(score2>score1 && *game_current->score2 < *game_current->score1) team2->wins++;
					if(score2<score1 && *game_current->score2 > *game_current->score1) team2->wins--;
					if(score2==score1 && *game_current->score2 > *game_current->score1) team2->wins--;
					if(score2>score1 && *game_current->score2 == *game_current->score1) team2->wins++;
					/* changing scores */
					*game_current->score1 = score1;
					*game_current->score2 = score2;
				}
				break;
			case 'g':;
				/* printing the best teams */
				printBestTeams(team_hash_table, NL);
				break;
			case 'r':;
				/* finding the game */
				game_current = findGame(game_hash_table, name);
				/* handling bad input */
				if(game_current==NULL) printf("%d Jogo inexistente.\n", NL);
				else {
					/* finding the teams */
					team1 = findTeam(team_hash_table, game_current->team1);
					team2 = findTeam(team_hash_table, game_current->team2);
					/* handling wins */
					if(*game_current->score1>*game_current->score2 && team1->wins>0) team1->wins--;
					else if(*game_current->score2>*game_current->score1 && team2->wins>0) team2->wins--;
					/* deleting from the reference list */
					deleteReference(&game_head, findReference(game_head, name));
					/* deleting from the game hash table */
					deleteGame(game_hash_table, name); 
				}
				break;
			case 'x':;
				/* freeing */
				free(command);
				free(name);
				free(team_name1);
				free(team_name2);
				freeGameHashTable(game_hash_table);
				freeTeamHashTable(team_hash_table);
				freeReference(game_head);
				/* terminating the program */
				return 0;
		}
	}
}
