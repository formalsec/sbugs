#include "jogos.h"



/*Function that initializes the hash table of games by making each head
  of the hash table NULL*/
void init_hash_games(NodeGame **heads,int mod)
{
    int i;
    for(i = 0; i < mod; i++){
        heads[i] = NULL;
    }
}

/*Function that creates a game, recieving its name, the name of the teams,
  and the score of the game, and returns the new game*/
Game * create_game(char *name,char *nameT1,char *nameT2,int goals1,int goals2)
{
    Game *newGame;
    char *nameGame, *nameTeam1, *nameTeam2;
    
    /*Allocation for the names of the game and the teams*/
    nameGame = str_dup(name);
    nameTeam1 = str_dup(nameT1);
    nameTeam2 = str_dup(nameT2);
    
    /*Allocation of memory for a new game*/
    newGame = (Game*) malloc(sizeof(Game));

    newGame->name = nameGame;
    newGame->team1 = nameTeam1;
    newGame->team2 = nameTeam2;
    newGame->score1 = goals1;
    newGame->score2 = goals2;

    return newGame;
}

/*Function that inserts in the hash table of games a new game*/
void hash_insert_game(NodeGame **heads,Game *game,int mod)
{
    /*searching for the hash key of the name of the game*/
    int key = hash(game->name,mod);

    heads[key] = hash_put_begin_games(heads[key], game);
}

/*Function that recieves the heads of the hash table of games and
  game and adds it to the beginning of the list of its respective
  hash key,returning the altered hash table*/
NodeGame * hash_put_begin_games(NodeGame *head,Game *game)
{
    NodeGame *newHead = (NodeGame*) malloc(sizeof(NodeGame));

    newHead->game = game;
    newHead->next = head; 
    head = newHead;
    
    return head;
}

/*Function that recieves the heads of the hash table of games and
  the name of a game and the module used for the hash table, and
  it returns the game to which the name of the game corresponds*/
Game * hash_search_game(NodeGame **heads,char *nameGame,int mod)
{
    int key = hash(nameGame,mod);
    return search_game(heads[key],nameGame);
}

/*Function that iterates through the several lists that constitute
  the hash table in search of the game to which the name given
  corresponds*/
Game * search_game(NodeGame *head,char *nameGame)
{   
    NodeGame *current = head;
    char *currentName;
    
    /*Cycle that will iterate through the list to find the game 
      to which the name of the game corresponds*/
    while(current != NULL){
        currentName = current->game->name;
        if(strcmp(currentName,nameGame) == 0){

            return current->game;

        }
        current = current->next;
    }
    return NULL;
}

/*Function that recieve the head os the hash table of gammes, the name of 
  a game, and the new score of a game, and it changes the score of the game
  in its respective game*/
void hash_change_score(NodeGame **heads,char *nameGame, int goals1, int goals2,
                       int mod)
{
    int key;
    NodeGame *current;
    
    /*Searching for the list that has the same hash key as the
      wanted game*/
    key = hash(nameGame,mod);
    current = heads[key];

    /*while cycle that iterates through the list of the hash key of
      the name of the game until it finds the game that corresponds*/
    while(strcmp(current->game->name,nameGame) != 0){
        current = current->next;
    }

    /*Changing the score of the game*/
    current->game->score1 = goals1;
    current->game->score2 = goals2;
}

/*Function that recieves the name of a game, and it removes the game
  that it corresponds from the database, and it 
  returns the altered hash table*/
void hash_remove_game(NodeGame **heads,char *nameGame,int mod)
{
    int key = hash(nameGame,mod);
    heads[key] = remove_el_hash(heads[key],nameGame);
}

/*Function that recieves that head of a list from the hash table
  which contains the game and the name of the game that is to removed
  and it removes that game from the database, returning the new list*/
NodeGame * remove_el_hash(NodeGame *head, char *gameName)
{
    NodeGame *t, *prev;

    /*for cycle that finds the game in the list of the hash table
      in which the game is*/
    for(t = head, prev = NULL; t != NULL;
        prev = t, t = t->next) {
            if(strcmp(t->game->name, gameName) == 0) {
                /*If the game is the first game of the list, then
                  the new head will be the next game*/
                if(t == head){
                    head = t->next;
                }
                /*If the game is not the head of the list, then
                  make the necessary connection so that the list remains
                  intact*/
                else{
                    prev->next = t->next;
                }

                /*Removing the game from the hash table of games and the program*/
                free_game(t->game);
                free(t);
                break;
            }
    }
 return head;
}

/*Function that recieves the head of the references list, and the name of
  the game to be removed, and it returns the head of the list with the
  reference to the game removed*/
NodeGame * remove_el_list(NodeGame *head, char *gameName)
{
    NodeGame *t, *prev;
    
    /*for cycle that iterates through the list until it finds the
      reference to the game to be removed*/
    for(t = head, prev = NULL; t != NULL;
        prev = t, t = t->next) {
            if(strcmp(t->game->name, gameName) == 0) {
                /*If the reference is the first game of the list, then
                  the new head will be the next reference*/
                if(t == head){
                    head = t->next;
                }
                /*If the reference is not the head of the list, then
                  make the necessary connection so that the list remains
                  intact*/
                else{
                    prev->next = t->next;
                }

                /*Eliminate the reference to the game in the hash table
                  from the list*/
                free(t);
                break;
            }
    }
 return head;
}

/*Function that recieves a game and removes it from the database
  by freeing the memory alloctated for it*/
void free_game(Game *game)
{
    free(game->name);
    free(game->team1);
    free(game->team2);
    free(game);
}

/*Function that recieves the heads of the lists that constitute
  the hash table of games and the module used for it, and it 
  deletes the hash table from the database*/
void destroy_hash_games(NodeGame **heads, int mod)
{
    int i;
    for(i = 0; i < mod;i++){
        destroy_list_games(heads[i]);
    }
}

/*Function that recieves an head of a list from the hash table
  of games and it deletes the list from the hash table*/
void destroy_list_games(NodeGame *head)
{
    NodeGame *aux;

    while((aux = head) != NULL){
        head = head->next;
        
        free_game(aux->game);
        free(aux);
    }
    head = NULL;
}

/*Function that recieves the head of the references list and
  it deletes the list from the database*/
void destroy_refs_list(NodeGame *head)
{
    NodeGame *aux;

    while((aux = head) != NULL){
        head = head->next;
        free(aux);
    }
    head = NULL;
}



