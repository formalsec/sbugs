#ifndef main_h_106
#define main_h_106

/* Used to store both game and team data
in team data: 
  score1 = how many wins the team has   
  name =  the name of the team
To use it in team mode, set the team_flag to 1*/
typedef struct game{
    int team_flag;
    int score1, score2, *index;
    char *team1, *team2;

} Game;

#include "linked_list.h"
#include "hash_table.h"
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define ARRAY_SIZE 1699
#define STRING_SIZE 1024



/* Receives a command and parses said command, calling the respective
fucntion and takes care any potential "junk" from the input stream */
Node_ptr parse_instructions(int command, int counter, Hash_Array *game_hash, Hash_Array *team_hash, Node_ptr top_game_list);
/* Exits the program, and frees all the variables */
void exit_program(Hash_Array *team_hash, Hash_Array *game_hash, Node_ptr top_game_list);


/* Adds a new team - name */
int comando_A(int counter, Hash_Array *team_hash);
/* Finds a certain team  */
int comando_P(int counter, Hash_Array *team_hash);
/* Adds a game - name:team1:team2:score1:score2 */
Node_ptr comando_a(int counter, Hash_Array *game_hash, Hash_Array *team_hash, Node_ptr top_game_list);
/* List all of the games */
int comando_l(int counter, Hash_Array *game_hash, Node_ptr top_game_list);
/* Looks for a game using the name - name */
int comando_p(int counter, Hash_Array *team_hash);
/* Deletes a game - name */
Node_ptr comando_r(int counter, Hash_Array *game_hash, Hash_Array *team_hash, Node_ptr top_game_list);
/* Changes the score of a given game - name:score1:score2*/
int comando_s(int counter, Hash_Array *ame_hash, Hash_Array *team_hash);
/* Finds the teams with most wins and sorts them by lexicographic order */
int comando_g(int counter, Hash_Array *team_hash);

/* Receives a string and will resize the string in order to save space */
char* resize_string(char *string);
/* Reads string input from user and resizes the array to the size of the string */
char* read_string();


#endif