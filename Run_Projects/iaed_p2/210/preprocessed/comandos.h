#include "Tables.h"

#define INITIAL_SIZE_HTABLES 200
#define INITIAL_SIZE_LISTS 100
#define MAX_STRINGS 1023

/*______________Prototypes_of_the_comand_functions_________________*/

void init();

/*case 'a'*/
void add_game(char *name, int linha, char *nameE1, char *nameE2, int score1, int score2);

/*case 'A'*/
void add_team(char *name, int linha);

/*case 'p'*/
void search_game(char *name);

/*case 'P'*/
void search_team(char *name);

/*case 'r'*/
void delete_game(char *name, int linha);

/*case 's'*/
void change_score(char *name, int score1, int score2, int linha);

/*case 'l'*/
void print_games(int linha);

/*case 'g'*/
void print_teams(int linha);

/*case 'x'*/
void free_all();