#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include "hashtable.h"
#include "data.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*==========================AUXILIAR==========================*/
int Hash(char *name, int size){
    int hash = 0;

    /*Random prime number to multiply*/
    int prime = 421;

    for( ; *name != '\0' ; name++){
        
        hash = (prime * hash + *name) % size;
    }

    return hash;
}


/*Used to compare in qsort*/
int compare(const void *t1, const void *t2){    
    return strcmp((*(Team*) t1)->name , (*(Team*) t2)->name);
}



/*==========================TEAMS==========================*/
HT_Team NewHT_Team(int size){
    int i;

    /*Reserves memory for a team hashtable structure*/
    HT_Team Teams = (HT_Team) can_fail_malloc(sizeof(teamht));
    
    /*Reserves memory for the hashtable*/
    Teams->ht = (Team*) can_fail_malloc(sizeof(Team) * size);

    /*Puts every pointer pointing to NULL*/
    for(i = 0 ; i < size ; i++){
        (Teams->ht)[i] = NULL;
    }

    /*Puts the number of Teams equal to 0*/
    Teams->num = 0;

    /*Puts the size of the hashtable equal to the size from the
    input*/
    Teams->size = size;

    return Teams;
}


void DeleteHT_Team(HT_Team Teams){
    int i;
    int size = Teams->size;

    /*Goes throught the hashtable*/
    for(i = 0; i < size ; i++){

        /*If it finds a team deletes it*/
        if((Teams->ht)[i] != NULL){
            DeleteTeam((Teams->ht)[i]);
        }
    }

    /*Frees the hashtable*/
    free(Teams->ht);

    /*Frees the hashtable structure*/
    free(Teams);
}


void InsertHT_Team(HT_Team Teams, Team team){
    char *name;
    int i;
    int size = Teams->size;

    /*Finds the name of the team*/
    name = NameTeam(team);

    /*Finds the hash value for the name*/
    i = Hash(name, size);

    /*Finds an available space for the team*/
    while((Teams->ht)[i] != NULL){

        /*Increses the index(uses mod size to keep it inside the 
        possible values for index)*/
        i = (i+1) % size;
    }

    /*Puts the team in the available space*/
    (Teams->ht)[i] = team;

    /*Increses the number of teams in the hash*/
    (Teams->num)++;

    /*If the number of teams exceed half of the hashtable size,
    increases the hashtable size by double*/
    if((Teams->num) > ((Teams->size)/2)){
        ExpandHT_Team(Teams);
    }
}


Team SearchHT_Team(HT_Team Teams, char *name){
    int i;
    int size = Teams->size;

    /*Finds a hash value for the name*/
    i = Hash(name, size);

    /*If it finds a NULL vector before finding the team with the same name
    then that team doesnt exist*/
    while((Teams->ht)[i] != NULL ){ 

        if(strcmp(NameTeam((Teams->ht)[i]), name) == 0){
            return (Teams->ht)[i];
        } 
        
        /*Increses the index(uses mod size to keep it inside the 
        possible values for index)*/
        i = (i+1) % size;
    } 
    
    /*Returns NULL if it doesnt exist*/
    return NULL;
}


void ExpandHT_Team(HT_Team Teams){
    int i;
    Team team;
    HT_Team tmp_teams;
        
    /*Size of the new hashtable*/
    int new_size = 2 * Teams->size;

    /*Creates a temporary HT_Team*/
    tmp_teams = NewHT_Team(new_size);

    /*With the size increase its needed to reinsert the contents
     of the old hashtable in the new one*/
    for(i = 0; i < new_size/2 ; i++){
        team = (Teams->ht)[i];

        if(team != NULL){
            /*Inserts the team from the old hashtable in the new*/
            InsertHT_Team(tmp_teams, team);
        }
    }

    /*Frees the hashtable*/
    free(Teams->ht);

    /*Changes the hashtable and the size value*/
    Teams->ht = tmp_teams->ht;
    Teams->size = tmp_teams->size;

    /*Frees the temporary HT_Team*/
    free(tmp_teams);
}


void HighestWin(HT_Team Teams, int NL){
    Team team;
    Team *teams = NULL;
    int i;
    int size = Teams->size;
    int nteams = 0;
    int win = 0;

    /*If theres no teams*/
    if((Teams->num) == 0){
        return;
    }

    /*Searches for the higher value of a win*/
    for(i = 0 ; i < size ; i++){
        team = (Teams->ht)[i];

        if(team != NULL){
            if((team->wins) > win){
                win = team->wins;
            }
        }
    }

    /*Creates an array with the adress of each team that has 
    wins equal to the value of the highest*/
    for(i = 0 ;  i < size ; i++){
        team = (Teams->ht)[i];

        if(team != NULL){
            if((team->wins) == win){

                /*Increases the number of team in the array*/
                nteams++;

                /*Increases the array size*/
                teams = (Team*) can_fail_realloc(teams, sizeof(Team) * nteams);

                /*Adds the new team*/
                teams[nteams-1] = team;
            }
        }
    }

    /*Sorts the teams in the array in lexicography order*/
    qsort(teams, nteams, sizeof(Team), compare);

    /*Goes through the array printing the results*/
    printf("%d Melhores %d\n", NL, win);
    for(i = 0 ; i < nteams ; i++){
        printf("%d * %s\n", NL, teams[i]->name);
    }

    /*Frees the array*/
    free(teams);
}



/*==========================GAMES==========================*/
HT_Game NewHT_Game(int size){
    int i;

    /*Reserves memory for a game hashtable structure*/
    HT_Game Games = (HT_Game) can_fail_malloc(sizeof(gameht));

    /*Reserves memory for the hashtable*/
    Games->ht = (Game*) can_fail_malloc(sizeof(Game) * size);

    /*Puts every pointer pointing to NULL*/
    for(i = 0 ; i < size ; i++){
        (Games->ht)[i] = NULL;
    }

    /*Puts the number of Games equal to 0*/
    Games->num = 0;

    /*Puts the size of the hashtable equal to the size from the
    input*/
    Games->size = size;

    return Games;
}


void DeleteHT_Game(HT_Game Games){
    int i;
    int size = Games->size;

    /*Goes throught the hashtable*/
    for(i = 0; i < size ; i++){

         /*If it finds a game deletes it*/
        if((Games->ht)[i] != NULL){
            DeleteGame((Games->ht)[i]);
        }
    }

    /*Frees the hashtable*/
    free(Games->ht);

    /*Frees the hashtable structure*/
    free(Games);
}


void InsertHT_Game(HT_Game Games, Game game){
    char *name;
    int i;
    int size = Games->size;

    /*Finds the name of the team*/
    name = NameGame(game);

    /*Finds the hash value for the name*/
    i = Hash(name, size);

    /*Finds an available space for the game*/
    while((Games->ht)[i] != NULL){

        /*Increses the index(uses mod size to keep it inside the 
        possible values for index)*/
        i = (i+1) % size;
    }

    /*Puts the game in the available space*/
    (Games->ht)[i] = game;

    /*Increses the number of games in the hash*/
    (Games->num)++;

    /*If the number of games exceed half of the hashtable size,
    increases the hashtable size by double*/
    if((Games->num) > ((Games->size)/2)){
        ExpandHT_Game(Games);
    }
}


void RemoveHT_Game(HT_Game Games, Game game){
    int k;
    int i;
    int size = Games->size;
    Game tmp;

    /*Finds the index of the game in the hashtable*/
    i = Hash(NameGame(game), size);
    while((Games->ht)[i] != game){
        i = (i+1) % size;
    }

    /*Deletes the content of the game*/
    DeleteGame(game);

    /*Reduces the number of Games*/
    (Games->num)--;

    /*Pointer now points to NULL*/
    (Games->ht)[i] = NULL;

    /*A free space appeared in the hash table so its needed to reallocate
    all of the data in front of the deleted game until it finds a NULL
    Increses the index(uses mod size to keep it inside the 
    possible values for index)*/
    for(k = (i+1) % size ; (Games->ht)[k] != NULL ; k = (k+1) % size){

        /*Copies the adress of a game that was found and replaces the adress
        in the old pointer with NULL*/
        tmp = (Games->ht)[k];
        (Games->ht)[k] = NULL;

        /*Counterbalance with the increase in InsertHT_Game,
        keeps the number of Games the same*/
        (Games->num)--;

        /*Reinserts the game in the hashtable*/
        InsertHT_Game(Games, tmp);
    }
}


Game SearchHT_Game(HT_Game Games, char *name){
    int i ;
    int size = Games->size;

    /*Finds a hash value for the name*/
    i = Hash(name, size);

    /*If it finds a NULL vector before finding the game with the same name
    then that game doesnt exist*/
    while((Games->ht)[i] != NULL ){ 

        if(strcmp(NameGame((Games->ht)[i]), name) == 0){
            return (Games->ht)[i];
        }

        /*Increses the index(uses mod size to keep inside the 
        possible values for index)*/
        i = (i+1) % size;
    } 
    
    /*Returns NULL if it doesnt exist*/
    return NULL;
}


void ExpandHT_Game(HT_Game Games){
    int i;
    Game game;
    HT_Game tmp_game;

    /*Size of the new hashtable*/
    int new_size = 2 * (Games->size);


    /*Creates a temporary HT_Game*/
    tmp_game = NewHT_Game(new_size);

    /*With the size increase its needed to reinsert the contents
     of the old hashtable in the new one*/
    for(i = 0; i < new_size/2 ; i++){
        game = (Games->ht)[i];

        if(game != NULL){
            /*Inserts the team from the old hashtable in the new*/
            InsertHT_Game(tmp_game, game);
        }
    }

    /*Frees the hashtable*/
    free(Games->ht);

    /*Changes the hashtable and the size value*/
    Games->ht = tmp_game->ht;
    Games->size = tmp_game->size;

    /*Frees the temporary HT_Game*/
    free(tmp_game);
}