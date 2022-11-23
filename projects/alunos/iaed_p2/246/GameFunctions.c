#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include "structs.h"

/*##################################################################################################

Command_a inserts(if not already in) all the informaticion about a game in the hashtable
'htable_game'. If the game already exists or if any of the teams of that game are non-existent there
will be an error message if not the function acts normally.

##################################################################################################*/
link_game command_a(link_game *htable_game,link_team *htable_team, char *name, char *t1, char *t2, 
int r1, int r2, int NL_counter){
    int a = hash(name);
    link_game aux = NULL;
    link_team aux_1 = lookup_team(htable_team, t1);
    link_team aux_2 = lookup_team(htable_team, t2);
    if (lookup_game(htable_game, name) != NULL){
        printf("%d Jogo existente.\n", NL_counter);
    }
    else if (aux_1 == NULL || aux_2 == NULL ){
        printf("%d Equipa inexistente.\n", NL_counter);
    }
    else{
        aux = NEWgame(name, aux_1, aux_2, r1, r2);
        aux->next = htable_game[a];
        htable_game[a] = aux;

        if (r1 > r2){
            aux_1->v += 1;
        }                    /*compares the results and adds a win to the respective team*/
        else if (r1 < r2){
            aux_2->v += 1;
        } 
        return aux;
    }
    return aux;
}

/*##################################################################################################

Command_l list the games(game name, home team, away team, home team score and away team score) in 
the order they were entered. 

command_l is a recursive function.

##################################################################################################*/

void command_l(link_game_order ordergamelist, int NL_counter){
    if(ordergamelist == NULL){
        return;
    }
    command_l(ordergamelist->next, NL_counter);
    printf("%d %s %s %s %d %d\n",NL_counter ,ordergamelist->element->name, 
        ordergamelist->element->element_t1->name, ordergamelist->element->element_t2->name, 
        ordergamelist->element->r1, ordergamelist->element->r2);
}

/*##################################################################################################

Command_p Look for a game by the given name and if that game exists command_p prints all the
information about that game. if the game doesn't exist the function prints an error message.

##################################################################################################*/

void command_p(link_game *htable_game, char *name, int NL_counter){
    link_game game = lookup_game(htable_game, name);
    if (game != NULL){
        printf("%d %s %s %s %d %d\n",NL_counter, game->name, game->element_t1->name, 
        game->element_t2->name, game->r1, game->r2);
    }
    else{
        printf("%d Jogo inexistente.\n", NL_counter);
    }
    return;
}

/*##################################################################################################

Command_r deletes a game from both the HashTable and the linkedlist if such a game exists

##################################################################################################*/

link_game_order command_r(link_game *htable_game, link_game_order head, char* text, int NL_counter){
    int a = hash(text);
    link_game tempGame;
    link_game_order t, prev;
    tempGame = lookup_game(htable_game, text);
    if(tempGame == NULL){
        printf("%d Jogo inexistente.\n", NL_counter);
        return head;
    }
    else{    
        for(t = head, prev = NULL; t != NULL; prev = t, t = t->next) {
            if(strcmp(t->element->name, text) == 0) { /*here the program finds the node where the*/ 
                if(t == head)                         /*the game that will be eliminated is*/
                    head = t->next;
                else
                    prev->next = t->next;/*set the pointers to the right way with the game*/
                free(t);                 /*eliminated*/
                break;
                }
            }
        if(tempGame->r1 > tempGame->r2){
            tempGame->element_t1->v--;
            }                        /*updates the teams victory after the game has been removed*/
        else if(tempGame->r1 < tempGame->r2){
            tempGame->element_t2->v--;
            }
        htable_game[a] = deletegame(htable_game[a], text); /*removes the game from the hash tabel*/
            }
    return head;
}

/*##################################################################################################

Command_s changes the score of a game if the same game exists, otherwise it prints an error message

##################################################################################################*/

int command_s(link_game *htable_game, char *GameName, int score1, int score2, int NL_counter){
    link_game auxGame;
    auxGame = lookup_game(htable_game, GameName);
    if(auxGame == NULL){
        printf("%d Jogo inexistente.\n", NL_counter);
        return 0;
    }
    else{
        if(auxGame->r1 >auxGame->r2){
            auxGame->element_t1->v--;
        }                              /*subtracts 1 victory from the team that previously won*/
        if(auxGame->r1 < auxGame->r2){
            auxGame->element_t2->v--;
        }
        if (score1 > score2){
            auxGame->element_t1->v++;
        }                       /*checks the new result and add 1 victory to the correct team*/
        if (score1 < score2){
            auxGame->element_t2->v++;
        }
        auxGame->r1 = score1;
        auxGame->r2 = score2;
        return 1;
    }
    return 0;
}