#ifndef STACKTEAMS_H
#define STACKTEAMS_H


/*
    structures
*/

typedef struct games_stack{
    char *name; 
    struct games_stack *next;
}stacks;

/*
    functions
*/

/*creating the pointer with a given name*/
stacks* create_game_stack(char *name);
/*inserts a new game in the stack in the correct order*/
void insert_game_stack(char *name, stacks **stack, stacks **head_stack);
/*removes a game from the stack*/
void remove_game_stack(stacks **stack, games *game, stacks **head);
/*print the stack*/
void print_stack(games **lst_games, stacks **stack, int nl);
/*free the stack_games*/
void free_stack_games(stacks **stack, stacks **head);

#endif