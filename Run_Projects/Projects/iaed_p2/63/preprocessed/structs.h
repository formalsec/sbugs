#ifndef STRUCTS
#define STRUCTS

#define MAX_CHAR 1024 /*Maximum characters for the game or team*/

typedef struct stru_team {
    /*array with the team name*/
    char *name; 
    /*counter for the games won*/
    int games_won;
} team;

typedef struct stru_node_teams {
    /*links to the next and previous nodes in the double linked list*/
    struct stru_node_teams *next;
    struct stru_node_teams *prev;
    /*same as before but for the double linked list of the entry in the table*/
    struct stru_node_teams *next_in_hash_table;
    struct stru_node_teams *prev_in_hash_table;
    /*team of the node*/
    team t;
} node_teams;

typedef struct stru_game {
    /*array with the game name*/
    char *name; 
    /*pointer to team1*/
    node_teams *t_1;
    /*pointer to team2*/
    node_teams *t_2;
    /*game score*/
    int score1, score2;
} game;

typedef struct stru_node_games {
    /*links to the next and previous nodes in the double linked list*/
    struct stru_node_games *next;
    struct stru_node_games *prev;
    /*same as before but for the double linked list of the entry in the table*/
    struct stru_node_games *next_in_hash_table;
    struct stru_node_games *prev_in_hash_table;
    /*game of the node*/
    game g;
} node_games;

#endif