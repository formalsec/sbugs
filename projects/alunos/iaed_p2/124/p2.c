#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include "teams.h"
#include "games.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAME_LEN 1024
/* Max length of teams' and games' names */


char* strManip(char *string);
/* Return de mem adress where the string is in the heap, only allocates
the required space */

gLink addGame(gLink *hashGame, gLink gHead, tLink *hashTeam, int NL);
/* Adds a game to the system, if the teams of the game exist */

void listGames(gLink gHead, int NL);
/* List all the games in the system, by insertion order */

void findGame(gLink *hashGame, int NL);
/* Search for a game in the system, by is name, and prints it */

gLink delGame(gLink *hashGame, gLink gHead, tLink *hashTeam,int NL);
/* Erase a game from the system */

void changeScore(gLink *hashGame, tLink *hashTeam, int NL);
/* Change the score of a game, modifying teams' wins */

void addTeam(tLink *hashTeam, int NL);
/* Add a new team to the system */

void findTeam(tLink *hashTeam, int NL);
/* Search for a team in the system, by is name, and prints it */

void winningTeams(tLink *hashTeam, int NL);
/* Prints the most winning teams, by alphabetical order */

void freeEverything(gLink *hashGame, tLink *hashTeam, gLink gHead);
/* Frees all the memory allocated in the heap */

int main()
{
    char in;
    int NL = 1;     /* no. of command line executed */
    
    /* aux list for case 'l' */
    gLink gHead = NULL;

    /* hashtables' pointers */
    gLink *hashGame = NULL;
    tLink *hashTeam = NULL;
    
    /* Initiates hashtables */
    hashTeam = tInit(hashTeam);
    hashGame = gInit(hashGame);


    while((in = getchar()) != 'x')
    {
        switch(in)
        {
            case('a'):
                gHead = addGame(hashGame, gHead, hashTeam, NL);
                NL++;
                break;
            case('l'):
                listGames(gHead, NL);
                NL++;
                break;
            case('p'):
                findGame(hashGame, NL);
                NL++;
                break;
            case('r'):
                gHead = delGame(hashGame, gHead, hashTeam, NL);
                NL++;
                break;
            case('s'):
                changeScore(hashGame, hashTeam, NL);
                NL++;
                break;
            case('A'):
                addTeam(hashTeam, NL);
                NL++;
                break;
            case('P'):
                findTeam(hashTeam, NL);
                NL++;
                break;
            case('g'):
                winningTeams(hashTeam, NL);
                NL++;
                break;
        }
    }
    freeEverything(hashGame, hashTeam, gHead);
    return 0;
}

char* strManip(char *string)
/* Allocates only the necessary memory for the char vector passed as argument */
{   
    char *dest;
    int len;
    len = strlen(string);
    dest = (char*)can_fail_malloc(sizeof(char)*(len+1));
    dest = strcpy(dest, string);
    return dest;
}


gLink addGame(gLink *hashGame, gLink gHead, tLink *hashTeam, int NL)
/* Checks if game's teams are in hashTeam and if the game doesn't exist already.
   Then adds the game to hashGame and aux list gHead */
{
    pGame g;
    pTeam winnTeam; /*pointer to the winning team*/
    char name[NAME_LEN], team1[NAME_LEN], team2[NAME_LEN];
    int score1, score2;

    scanf(" %[^:\n]:%[^:\n]:%[^:\n]:%d:%d", 
          name, team1, team2, &score1, &score2);
    
    if (gHTsearch(hashGame, name) != NULL)
    {    
        printf("%d Jogo existente.\n", NL);
    }
    else if ((tHTsearch(hashTeam, team1) == NULL) || 
             (tHTsearch(hashTeam, team2) == NULL))    
    {
        printf("%d Equipa inexistente.\n", NL);
    }
    else    
    {
        g = (pGame) can_fail_malloc(sizeof(struct game));
        g->name = strManip(name);
        g->team1 = strManip(team1);
        g->team2 = strManip(team2);
        g->score1 = score1;
        g->score2 = score2;

        gHTinsert(hashGame, g);
        gHead = gInsert_begin(gHead, g);
        
        /*update team wins*/
        if (score1 > score2)
        {
            winnTeam = tHTsearch(hashTeam, team1);
            (winnTeam->wins)++;
        }
        else if (score2 > score1)
        {
            winnTeam = tHTsearch(hashTeam, team2);
            (winnTeam->wins)++;
        }
    }
    return gHead;
}


void listGames(gLink gHead, int NL)
/* Prints the games in list gHead, from the first inserted to the last one */
{
    if (gHead == NULL)  /* no games in the system */
        return;
    else
    {  
        /* find the last element in the list (1st inserted) */
        while (gHead->next != NULL)
        {
            gHead = gHead->next;
        }

        /* prints the games from bottom of the list to the top */
        do
        {
            printf("%d %s %s %s %d %d\n",
                NL, gHead->game->name, 
                gHead->game->team1, gHead->game->team2, 
                gHead->game->score1, gHead->game->score2);
                gHead = gHead->prev;
        } 
        while (gHead != NULL);
    }
}


void findGame(gLink *hashGame, int NL)
/* Search and print a game in the hashGame, looking for its name, if it exists*/
{
    pGame g;
    char name[NAME_LEN];
    scanf(" %[^:\n]",name);

    if ((g = gHTsearch(hashGame, name)) != NULL)
        printf("%d %s %s %s %d %d\n", NL, g->name, g->team1, g->team2, 
                                      g->score1, g->score2);

    else
        printf("%d Jogo inexistente.\n", NL);
}


gLink delGame(gLink *hashGame, gLink gHead, tLink *hashTeam, int NL)
/* Deletes game from hashGame and gHead, updating teams' wins in hashTeam */
{
    pGame g;
    pTeam t1, t2;
    char name[NAME_LEN];
    scanf(" %[^:\n]",name);

    g = gHTsearch(hashGame, name);


    if (g == NULL)
        printf("%d Jogo inexistente.\n", NL);

    else
    {
        t1 = tHTsearch(hashTeam, g->team1);
        t2 = tHTsearch(hashTeam, g->team2);
        if (g->score1 > g->score2)
            (t1->wins)--;
        else if (g->score1 < g->score2)
            (t2->wins)--;
        
        gHead = gRemove(gHead, name);
        gHTdelete(hashGame, name);
        freeGame(g);
    }   
    return gHead;
}


void changeScore(gLink *hashGame, tLink *hashTeam, int NL)
/* Changes score of a game in hashGame, updating teams' wins */
{
    pGame g;
    pTeam t1, t2;
    int score1, score2;
    char name[NAME_LEN];
    scanf(" %[^:\n] : %d : %d.",name, &score1, &score2);

    if (gHTsearch(hashGame, name) == NULL)
        printf("%d Jogo inexistente.\n", NL);
    
    else
    {
        g = gHTsearch(hashGame, name);
        t1 = tHTsearch(hashTeam, g->team1);
        t2 = tHTsearch(hashTeam, g->team2);

        if (g->score1 > g->score2 && score1 < score2)
        {
            (t1->wins)--;
            (t2->wins)++;
        }
        else if (g->score1 < g->score2 && score1 > score2)
        {
            (t1->wins)++;
            (t2->wins)--;
        }
        else if (g->score1 == g->score2)
        {
            if (score1 > score2)
                (t1->wins)++;
            else if (score1 < score2)
                (t2->wins)++;
        }
        else if (score1 == score2)
        {
            if (g->score1 > g->score2)
                (t1->wins)--;
            else if (g->score1 < g->score2)
                (t2->wins)--;


        }
        g->score1 = score1;
        g->score2 = score2;
    }
}


void addTeam(tLink *hashTeam, int NL)
/* checks if team doesn't exist, and adds it */
{
    pTeam t;
    char name[NAME_LEN];
    scanf(" %[^:\n]",name);
    
    if (tHTsearch(hashTeam, name) == NULL)
    {
        t = (pTeam) can_fail_malloc(sizeof(struct team));
        t->name = strManip(name);
        t->wins = 0;
        tHTinsert(hashTeam, t);
    }
    else
    {
        printf("%d Equipa existente.\n",NL);
    }
}


void findTeam(tLink *hashTeam, int NL)
/* Search for a team in hashTeam, and print it */
{
    pTeam team;
    char name[NAME_LEN];
    scanf(" %[^:\n]",name);

    if ((team = tHTsearch(hashTeam, name)) != NULL)
        printf("%d %s %d\n", NL, team->name, team->wins);

    else
        printf("%d Equipa inexistente.\n", NL);
}

void winningTeams(tLink *hashTeam, int NL)
/* lists the teams in hashTeam with most wins, alphabetically. */
{
    /* pointer to the head of aux list with most winning teams ordered by name*/
    tLink tHead = NULL; 
    /* aux node of team's list */
    tLink aux; 
    int i;
    int max = max_wins(hashTeam); /* number of wins of most winning team(s) */

    /* inserts team in list tHead if it's a most winning team */
    for (i = 0; i != H_LEN; i++)
    {
        aux = hashTeam[i];
        while(aux != NULL)
        {
            if (aux->team->wins == max)
            {
               tHead = alphInsert(tHead, aux->team); 
            }
            aux = aux->next;
        }
    }

    /* prints */
    if (tHead != NULL)
    {
        printf("%d Melhores %d\n",NL, max);
        while(tHead != NULL)
        {
            printf("%d * %s\n", NL, tHead->team->name);
            aux = tHead;
            tHead = tHead->next;
            free(aux);
        }
    }
}

void freeEverything(gLink *hashGame, tLink *hashTeam, gLink gHead)
/* 
    frees the memory allocated in all games (name and teams), 
    all teams (name), nodes in games aux list (gHead), nodes in hashtables
    (hashGame and hashTeam)
*/
{
    int i;
    tLink aux_team, aux_team2;
    gLink aux_game, aux_game2;
    for (i = 0; i != H_LEN; i++)
    {
        aux_team = hashTeam[i];
        aux_game = hashGame[i];
        while(aux_team != NULL)
        {
            aux_team2 = aux_team;
            aux_team = aux_team->next;
            freeTeam(aux_team2->team);
            free(aux_team2);
        }
        while(aux_game != NULL)
        {
            aux_game2 = aux_game;
            aux_game = aux_game->next;
            freeGame(aux_game2->game);
            free(aux_game2);
        }    
    }
    while (gHead != NULL)
    {
        aux_game = gHead;
        gHead = gHead->next;
        free(aux_game);
    }
    free(hashGame);
    free(hashTeam);
}