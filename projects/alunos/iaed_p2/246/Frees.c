#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include "structs.h"


/*##################################################################################################

freeHTgame frees the memory related to everything in the hashtable_game.

##################################################################################################*/
void freeHTgame(link_game *htable_game){
    int i;
    link_game aux;
    for (i = 0; i < TableSize; i++){
        while(htable_game[i] != NULL){
            aux = htable_game[i]->next;
            free(htable_game[i]->name);
            free(htable_game[i]);
            htable_game[i] = aux;
        }  
    }
    free(htable_game);
}

/*##################################################################################################

freeHTteam frees the memory related to everything in the hashtable_team.

##################################################################################################*/
void freeHTteam(link_team *htable_team){
    int i;
    link_team aux;
    for (i = 0; i < TableSize; i++){
        while(htable_team[i] != NULL){
            aux = htable_team[i]->next;
            free(htable_team[i]->name);
            free(htable_team[i]);
            htable_team[i] = aux;
        }  
    }
    free(htable_team);    
}

/*##################################################################################################

freeordergamelist frees the memory about everything in the linkedlist created for command_l.

##################################################################################################*/
void freeordergamelist(link_game_order head){
    link_game_order aux;
    while (head != NULL){
        aux = head->next;
        free(head);
        head = aux;
    }
}

/*##################################################################################################

freeGame frees only the memory related to one game in the htable_game.

##################################################################################################*/
void freeGame(link_game game){
    free(game->name);
    free(game);
}

/*##################################################################################################

freebetterLIST frees the memory related to the whole linkedlist that contains the teams in 
lexicographical order everytime the fucntion command_g occurs.

##################################################################################################*/
void freebetterLIST(link_Team_lexicographical_order *head){
    link_Team_lexicographical_order aux;
    while (*head != NULL){
        aux = (*head)->next;
        free(*head);
        *head = aux;
    }
}