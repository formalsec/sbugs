#ifndef Structures
#define Structures

#define MAX_INPUT 3100
#define MAX_WORD_SIZE 1024

struct game {
  char *name;
  char *team1;
  char *team2;
  int score1;
  int score2;
  int number; /*this will keep the game insert number*/
};
typedef struct game game;

struct team {
  char *name;
  int games_won;
};
typedef struct team team;

unsigned int hash (char* name, int size);

void teams_initialize (team* hash_table, int size);
void create_team (char *name, team *hash_table, int size, int counter, int *teams_number, int max_games_won, int *teams_with_max_games_won);
int teams_search (char *name, team *hash_table, int size);
void team_errors (int found, team *hash_table, int counter);
void team_increase_games_won (char *name, team *hash_table, int size,int* max_games_won, int* teams_with_max_games_won, int *second_max_games_won,int* teams_with_second_max_games_won);
void team_decrease_games_won (char *name, team *hash_table, int size,int* max_games_won, int* teams_with_max_games_won, int *second_max_games_won,int* teams_with_second_max_games_won, int teams_number);
void find_team_with_more_games_won (team *hash_table, int size, int teams_with_max_games_won, int max_games_won, int counter);
void free_teams(team *hash_table, int size);

void games_initialize (game* hash_table, int size);
void create_game (char *name, char *team1, char *team2, int score1, int score2, game *hash_table, int size, team *teams_hash_table, int teams_size,int counter, int *games_number, int *max_games_won, int*teams_with_max_games_won, int *number, int *second_max_games_won, int *teams_with_second_max_games_won);
int games_search (char *name, game *hash_table, int size);
void game_errors (int found, game *hash_table, int counter);
void remove_game (char* game_name, game *hash_table, int games_size, team* teams_hash_table, int teams_size, int *max_games_won, int *teams_with_max_games_won, int *second_max_games_won, int *teams_with_second_max_games_won,int teams_number,int *games_number,int counter);
void change_score(char* game_name, int team1_score, int team2_score, game *hash_table, int games_size, team* teams_hash_table, int teams_size, int *max_games_won, int *teams_with_max_games_won, int *second_max_games_won, int *teams_with_second_max_games_won,int games_number,int counter);
void list_all_the_games(game *hash_table, int size, int games_number, int counter);
void free_games(game *hash_table, int size);

#endif
