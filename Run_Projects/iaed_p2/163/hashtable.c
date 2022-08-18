#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "hashtable-structs.h"

/*LIST OF TEAMS*/
team_ptr NewTeamLink(char * team_name_var){
    /*creates a team to insert in a list*/
    team_ptr x = malloc(sizeof(struct team));

    x->team_name = malloc(sizeof(char) *(strlen(team_name_var) +1));
    strcpy(x->team_name, team_name_var);

    x->games_won = 0;

    x->next = NULL;
    return x;
}

team_ptr InsertBeginTeamList(team_ptr head, char* team_name_var){
    /*inserts in team list*/
    team_ptr x = NewTeamLink(team_name_var);
    x->next = head;
    return x;
}

team_ptr LookUpTeams(team_ptr head, char * team_name_var){
    /*returns the team by name*/
    team_ptr x;
    for(x= head; x!= NULL; x = x->next){
        if(strcmp(x->team_name, team_name_var) == 0){
            return x;
        }
    }
    return NULL;
}

void freeTeamList(team_ptr head){
    /*frees the heap from teams*/
    while(head != NULL) {
        team_ptr old;
        old = head;
        head = head->next;
        free(old->team_name);
        free(old);
    }
}


/*LIST FOR GAME TO SORT*/
link InsertGameList(link head, char* game_name_var, char*team1_var
                        , char*team2_var,
            int score1, int score2){
                /*inserts game in to a list for comand l*/
    link x ;
    if(head == NULL){
        return NewLink(game_name_var, team1_var, team2_var, score1, score2);
    }else{
        for(x = head; x->next != NULL; x = x->next);
        x->next = NewLink(game_name_var, team1_var, team2_var, score1, score2);
        return head;
    }
}

link ChangeScore(link head, char* game_name_var
                , int score1, int score2){
                    /*changes score of a game*/
    link x;
    for(x = head; x != NULL; x = x->next){
        if(strcmp(x->this_game->game_name, game_name_var) == 0){
            x->this_game->score_team1 = score1;
            x->this_game->score_team1 = score2;
            break;
        }
    }
    return head;
}


/*LIST FOR GAME HASHTABLE*/
link NewLink(char* game_name_var, char* team1_var, char* team2_var, 
            int score1, int score2){
                /*creates node with a game 
                to insert in hashtable*/

    link x = (link) malloc(sizeof(struct node));
    x->this_game = (game_ptr) malloc(sizeof(struct game));
    
    x->this_game->game_name = (char*) malloc(sizeof(char) * (strlen(game_name_var) + 1));
    strcpy(x->this_game->game_name, game_name_var);

    x->this_game->team1 = (char*) malloc(sizeof(char) * (strlen(team1_var) + 1));
    strcpy(x->this_game->team1, team1_var);
    
    x->this_game->team2 = (char*) malloc(sizeof(char) * (strlen(team2_var) + 1));
    strcpy(x->this_game->team2, team2_var);

    x->this_game->score_team1 = score1;
    x->this_game->score_team2 = score2;

    x->next = NULL;

    return x;
}

link InsertBegin(link head, char* game_name_var, char*team1_var, char*team2_var,
            int score1, int score2){
                /*inserts game in list for hashtable*/
    link x = NewLink(game_name_var, team1_var, team2_var, score1, score2);
    x->next = head;
    return x;
}

link LookUp(link head, char * game_name_var){
    /*returns node with a game, searched by a name*/    
    link x;
    for(x = head; x != NULL; x = x->next){
        if(x->this_game->game_name != NULL)
            if(strcmp(x->this_game->game_name, game_name_var) == 0)
                return x;
    }
    return NULL;
}

link Remove(link head, char* game_name_var){
    /*removes a game from a game list*/
    link x, prev;
    for(x = head, prev = NULL; x != NULL; prev = x, x = x->next){
        if(strcmp(x->this_game->game_name, game_name_var) == 0){
            if(x == head)
                head = x->next;
            else
                prev->next = x->next;

            
            free(x->this_game->team1);
            free(x->this_game->team2);
            free(x->this_game->game_name);
            free(x->this_game);
            free(x);
            break;
        }
    }
    return head;

    
}

void print_list(link head){
    link x;
    for(x=head; x != NULL; x = x->next)
        printf("%s %s %s %d %d\n", x->this_game->game_name
                                            , x->this_game->team1
                                            , x->this_game->team2
                                            , x->this_game->score_team1
                                            , x->this_game->score_team2);
}

void freeLink(link head){
    /*frees list of games*/
    while(head != NULL) {
        link old;
        old = head;
        head = head->next;
        free(old->this_game->team1);
        free(old->this_game->team2);
        free(old->this_game->game_name);
        free(old->this_game);
        free(old);
    }
    free(head);
}

/*HASHTABLE*/
int hash(char* game_name_var ,int size_table){
    /*returns the hashkey of a game*/
    int length = strlen(game_name_var);
    int i;
    int hashkey = 0;
    for(i=0; i < length; i++){
        hashkey += game_name_var[i];
    }

    return hashkey % size_table;
}

link* Init(link * heads, int size_table){
    /*inicializes hashtable*/
    int i;
    if(heads == NULL){
        heads = (link*) malloc(sizeof(link) * size_table);

        for(i=0; i < size_table; i++)
            heads[i] = NULL;
    }
    return heads;
}

void InsertInTable(link* hashtable, int size_table,
                    char* game_name_var, char*team1_var, char*team2_var,
            int score1, int score2){
                /*insert in hashtable*/
    int key = hash(game_name_var, size_table);
    hashtable[key] = InsertBegin(hashtable[key], game_name_var, team1_var, team2_var, score1, score2);

}

void RemoveFromTable(link* hashtable, int size_table, char * game_name_var){
    /*removes from hashtable*/
    int key = hash(game_name_var, size_table);
    hashtable[key] = Remove(hashtable[key], game_name_var);

}

game_ptr LookUpInTable(link* hashtable, char * game_name_var, int size_table){
    /*returns a game from the hashtable,
                     searched by a name*/
    int key = hash(game_name_var, size_table);
    if(hashtable != NULL){
        if(LookUp(hashtable[key], game_name_var) == NULL)
            return NULL;
        else
            return LookUp(hashtable[key], game_name_var)->this_game;
    }
    return NULL;
}


void DeleteHashtable(link* hashtable, int size_table){
    /*frees hashtable from the heap*/
    int i;
    if(hashtable != NULL){
        for(i=0; i< size_table; i++){
            freeLink(hashtable[i]);
        }
        free(hashtable);
    }
}

