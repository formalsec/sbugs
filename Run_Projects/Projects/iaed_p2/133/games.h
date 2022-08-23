#ifndef GAMES_H
#define GAMES_H

/*
    structures
*/

typedef struct games{
    char *name;
    char *team1;
    char *team2;
    int score1;
    int score2;
    struct games *next;
}games;


/*
    funtions
*/

/*initialize the list of games*/
void init_games(games **lst_games, int size);
/*creates a new game with a given name*/
games * new_game(games *game, char *name, char *team1, char *team2, int score1, int score2);
/*checks if a certain game already exits*/
int look_game(games **lst_games, char *name);/*returns 1 if it does, 0 if it doesnt*/
/*inserts a new team at the begging of the correct list*/
void insert_new_game(games **lst_games, games *new);/*returns the new head*/
/*get the pointer, game, that has a given name*/
games* get_game(games **lst_games, char * name);
/*know who won the game*/
int who_won(int score1, int score2);
/*remove a game from the list of games*/
void remove_game(games **lst_games, games *game);
/*clear the list*/
void clear_the_games(games **lst_games);

#endif